import asyncio
import os
# import openai
from openai import OpenAI
from constants import DEFAULT_DIR, DEFAULT_MODEL, DEFAULT_MAX_TOKENS, EXTENSION_TO_SKIP
GPT_MODEL = "gpt-3.5-turbo-0125"

def read_file(filename):
    with open(filename, 'r') as file:
        return file.read()

def walk_directory(directory):
    code_contents = {}
    for root, dirs, files in os.walk(directory):
        for file in files:
            if not any(file.endswith(ext) for ext in EXTENSION_TO_SKIP):
                try:
                    relative_filepath = os.path.relpath(os.path.join(root, file), directory)
                    code_contents[relative_filepath] = read_file(os.path.join(root, file))
                except Exception as e:
                    code_contents[relative_filepath] = f"Error reading file {file}: {str(e)}"
    return code_contents

async def generate_response(system_prompt, user_prompt, model=GPT_MODEL, *args):
    messages = [
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": user_prompt}
    ]

    # Add additional conversation history if any
    role = "assistant"
    for value in args:
        messages.append({"role": role, "content": value})
        role = "user" if role == "assistant" else "assistant"

    # Send the API request using the updated API call
    # response = await openai.ChatCompletion.acreate(**params)
    # return response['choices'][0]['message']['content']
    client = OpenAI()  # Create the OpenAI client
    response = client.chat.completions.create(         # get the request from the model
        model=GPT_MODEL,                               # Step 1: send the conversation 
        messages=messages,                             # and available functions to the model
    )                                                  # auto is default, but we'll be explicit
        
    print("Received response from OpenAI")
    response_message = response.choices[ 0 ].message
    return response_message.content

def main(prompt=None, directory=DEFAULT_DIR, model=DEFAULT_MODEL):
    code_contents = walk_directory(directory)

    # Create context from code contents
    context = "\n".join(f"{path}:\n{contents}" for path, contents in code_contents.items())
    system = ("You are an AI debugger who is trying to fully describe a program, in order for another AI program "
              "to reconstruct every file, data structure, function and functionality. The user has provided you "
              "with the following files and their contents:")
    prompt_text = "My files are as follows: " + context + "\n\n" + (f"Take special note of the following: {prompt}" if prompt else "")
    prompt_text += "\n\nDescribe the program in markdown using specific language that will help another AI program reconstruct the given program in as high fidelity as possible."

    print ( "\n\n\nPrompt:\n" + prompt_text + "\n\n\n")
    # write the prompt to a file
    with open("prompt.md", "w") as f:
        f.write( system + "\n\n" + prompt_text )
    res = asyncio.run(generate_response(system, prompt_text, model))
    print("\033[96m" + res + "\033[0m")
    # put the response in a file
    with open("response.md", "w") as f:
        f.write( res )

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Run the AI debugging script.")
    parser.add_argument("--prompt", type=str, help="Additional context or instructions for the AI.", default=None)
    parser.add_argument("--directory", type=str, help="Directory to scan for code files.", default=DEFAULT_DIR)
    parser.add_argument("--model", type=str, help="OpenAI model to use.", default=DEFAULT_MODEL)
    args = parser.parse_args()

    main(prompt=args.prompt, directory=args.directory, model=args.model)


  
