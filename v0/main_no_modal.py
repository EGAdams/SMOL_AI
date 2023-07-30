import sys
import os
import ast
from time import sleep
from utils import clean_dir
from constants import DEFAULT_DIR, DEFAULT_MODEL, DEFAULT_MAX_TOKENS

SMART_EXPENSIVE          = "gpt-4"
TURBO_MODEL              = "gpt-3.5-turbo"
SHARED_DEPENDENCIES_FILE = "shared_dependencies.md"

generatedDir            = "generated"
openai_model            = TURBO_MODEL   #"gpt-4"  # or 'gpt-3.5-turbo',
openai_model_max_tokens = 2000          # i wonder how to tweak this properly

def generate_response(system_prompt, user_prompt, *args):
    import openai
    import tiktoken
    import dotenv

    def reportTokens(prompt):
        encoding = tiktoken.encoding_for_model(DEFAULT_MODEL)
        # print number of tokens in light gray, with first 10 characters of prompt in green
        print(
            "\033[37m"
            + str(len(encoding.encode(prompt)))
            + " tokens\033[0m"
            + " in prompt: "
            + "\033[92m"
            + prompt[:50]
            + "\033[0m" )
    openai.api_key = dotenv.dotenv_values()["OPENAI_API_KEY"] # Set up your OpenAI API credentials
    messages = []
    messages.append({"role": "system", "content": system_prompt})
    reportTokens(system_prompt)
    messages.append({"role": "user", "content": user_prompt})
    reportTokens(user_prompt)
    role = "assistant"
    for value in args: # loop thru each arg and add it to messages alternating role between "assistant" and "user"
        messages.append({"role": role, "content": value})
        reportTokens(value)
        role = "user" if role == "assistant" else "assistant"

    params = {
        "model": DEFAULT_MODEL,
        "messages": messages,
        "max_tokens": openai_model_max_tokens,
        "temperature": 0 }

    keep_trying = True
    while keep_trying:
        try:
            response = openai.ChatCompletion.create(**params) # Send the API request
            keep_trying = False
        except Exception as e:
            # e.g. when the API is too busy, we don't want to fail everything
            print("Failed to generate response. Error: ", e)
            sleep(30)
            print("Retrying...")

    # Get the reply from the API response
    reply = response.choices[0]["message"]["content"]
    return reply


def generate_file(
    filename, filepaths_string=None, shared_dependencies=None, prompt=None
):
    filecode = generate_response( # call openai api with this prompt
        f"""You are an AI developer who is trying to write a program that will generate code for the user based on their intent.

    the purpose of our app is: {prompt}

    the files we have decided to generate are: {filepaths_string}

    the shared dependencies (like filenames and variable names) we have decided on are: {shared_dependencies}

    only write valid code for the given filepath and file type, and return only the code.
    do not add any other explanation, only return valid code for that file type.
    """,
        f"""
    We have broken up the program into per-file generation.
    Now your job is to generate only the code for the file {filename}.
    Make sure to have consistent filenames if you reference other files we are also generating.

    Remember that you must obey 3 things:
       - you are generating code for the file {filename}
       - do not stray from the names of the files and the shared dependencies we have decided on
       - MOST IMPORTANT OF ALL - the purpose of our app is {prompt} - every line of code you generate must be valid code. Do not include code fences in your response, for example

    Bad response:
    ```javascript
    console.log("hello world")
    ```

    Good response:
    console.log("hello world")

    Begin generating the code now.

    """,
    )
    return filename, filecode

def main(prompt, directory=generatedDir, file=None):
    if prompt.endswith(".txt"): # read file from prompt if it ends in a .md filetype
        with open(prompt, "r") as promptfile:
            prompt = promptfile.read()
    print("hi its me, 🐣the smol developer🐣! you said you wanted:")
    print("\033[92m" + prompt + "\033[0m") # print the prompt in green color
    # example prompt: a Chrome extension that, when clicked, opens a small window with a page where you can enter a 
    # prompt for reading the currently open page and generating some response from openai.
    filepaths_string = generate_response( # call openai api with this prompt
        """You are an AI developer who is trying to write a program that will generate code for the user based on their intent.

    When given their intent, create a complete, exhaustive list of filepaths that the user would write to make the program.

    only list the filepaths you would write, and return them as a python list of strings.
    do not add any other explanation, only return a python list of strings.
    """,
        prompt,
    )
    print(filepaths_string)
    # print ok? to get user input
    input("\033[92m" + "ok? " + "\033[0m")
    # parse the result into a python list
    list_actual = []
    try:
        list_actual = ast.literal_eval( filepaths_string )
        shared_dependencies = None
        if os.path.exists( SHARED_DEPENDENCIES_FILE ): # if shared_dependencies.md is there, read it in, else leave as None
            with open( SHARED_DEPENDENCIES_FILE , "r") as shared_dependencies_file:
                shared_dependencies = shared_dependencies_file.read()

        if file is not None:
            print("file", file) # check file
            filename, filecode = generate_file(
                file,
                filepaths_string    = filepaths_string,
                shared_dependencies = shared_dependencies,
                prompt=prompt )
            write_file(filename, filecode, directory)
        else:
            clean_dir(directory)
            shared_dependencies = generate_response(  # understand shared dependencies
                """You are an AI developer who is trying to write a program that will generate code for the user based on their intent.

            In response to the user's prompt:

            ---
            the purpose of our app is: {prompt}
            ---

            the files we have decided to generate are: {filepaths_string}

            Now that we have a list of files, we need to understand what dependencies they share.
            Please name and briefly describe what is shared between the files we are generating, including exported variables, data schemas, id names of every DOM elements that javascript functions will use, message names, and function names.
            Exclusively focus on the names of the shared dependencies, and do not add any other explanation.
            """,
                prompt,
            )
            print( shared_dependencies )
            write_file( SHARED_DEPENDENCIES_FILE , shared_dependencies, directory) # write as a md file inside generated dir
            for name in list_actual:
                filename, filecode = generate_file(
                    name,
                    filepaths_string    = filepaths_string,
                    shared_dependencies = shared_dependencies,
                    prompt              = prompt,
                )
                write_file(filename, filecode, directory)

    except ValueError:
        print( "Failed to parse result in path: ", filepaths_string )

def write_file( filename, filecode, directory ):
    print("\033[94m" + filename + "\033[0m")  # Output the filename in blue color
    print( filecode )
    file_path = directory + "/" + filename
    directory_from_filepath = os.path.dirname( file_path )
    os.makedirs( directory_from_filepath, exist_ok=True )
    with open( file_path, "w" ) as file:  # Open the file in write mode
        file.write( filecode )            # Write content to the file

def clean_dir(directory):
    extensions_to_skip = [
        ".png",
        ".jpg",
        ".jpeg",
        ".gif",
        ".bmp",
        ".svg",
        ".ico",
        ".tif",
        ".tiff",
        ".txt"
    ]  # Add more extensions if needed

    if os.path.exists(directory): # Check if the directory exists
        for root, dirs, files in os.walk(directory): # If it does, iterate over all files and directories
            for file in files:
                _, extension = os.path.splitext(file)
                if extension not in extensions_to_skip:
                    os.remove(os.path.join(root, file))
    else:
        os.makedirs(directory, exist_ok=True)

if __name__ == "__main__":

    # Check for arguments
    if len(sys.argv) < 2:
        print( "Please provide a prompt" )
        sys.exit(1)
    prompt = sys.argv[1]
    directory = sys.argv[2] if len(sys.argv) > 2 else generatedDir
    file = sys.argv[3] if len(sys.argv) > 3 else None

    # Run the main function
    main(prompt, directory, file)
