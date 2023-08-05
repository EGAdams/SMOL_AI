import os
from time import sleep
DEFAULT_DIR             = "/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/"
OBJECT_OF_INTEREST      = "PinInterface"
TURBO_MODEL             = "gpt-3.5-turbo"

def read_file(filename):
    with open(filename, "r" ) as file:
        return file.read()

def walk_directory(directory):
    image_extensions = [ ".png", ".jpg", ".jpeg", ".gif", ".bmp", ".svg", ".ico", ".tif", ".tiff" ]
    code_contents = {}
    for root, dirs, files in os.walk(directory):
        for file in files:
            if not any(file.endswith(ext) for ext in image_extensions):
                try:
                    relative_filepath = os.path.relpath(
                        os.path.join(root, file), directory
                    )
                    code_contents[relative_filepath] = read_file(
                        os.path.join(root, file)
                    )
                except Exception as e:
                    code_contents[
                        relative_filepath
                    ] = f"Error reading file {file}: {str(e)}"
    return code_contents

def main():
    prompt          = read_file( DEFAULT_DIR + "make_error_prompt.md" ) # the error message
    directory       = DEFAULT_DIR + OBJECT_OF_INTEREST                  # the object's directory
    model           = TURBO_MODEL                                       # the model to use
    code_contents   = walk_directory( directory ) # code_contents will contain all of the code.
    context         = "\n".join( f"{path}:\n{contents}" for path, contents in code_contents.items())
    system          = "You are an AI debugger who is trying to debug a C++ project based on the current file system. You are provided with the following files and their contents, finally folllowed by the error message or issue we are facing now."

    prompt =  ( "My files are as follows:\n```\n" + context + "```\n\n" + "My issue is as follows: " + prompt )
    prompt += ( "\n\nAct as a world-class, expert C++ project debugger and give me ideas for what could be wrong and what fixes to do in which files." )
    
    with open( "temp.md", "w" ) as file: # write prompt contents into temp.md
        file.write( prompt )

    print( "\033[96m" + generate_response( system, prompt, model ) + "\033[0m" ) # print res in teal
    # delete temp.md
    os.remove( "temp.md" )
    
def generate_response(system_prompt, user_prompt, model=TURBO_MODEL, *args):
    import openai
    openai.api_key = os.environ[ "OPENAI_API_KEY" ] # Set up your OpenAI API credentials
    messages = []
    messages.append({"role": "system", "content": system_prompt})
    messages.append({"role": "user", "content": user_prompt})
    # loop thru each arg and add it to messages alternating role between "assistant" and "user"
    role = "assistant"
    for value in args:
        messages.append({"role": role, "content": value})
        role = "user" if role == "assistant" else "assistant"
    params = { "model": model, "messages": messages, "max_tokens": 1500, "temperature": 0 }
    keep_trying = True
    while keep_trying:  # Send the API request
        try:
            response = openai.ChatCompletion.create( **params )
            keep_trying = False
        except Exception as e:
            # e.g. when the API is too busy, we don't want to fail everything
            print( "Failed to generate response. Error: ", e)
            sleep( 30 )
            print( "Retrying..." )
    reply = response.choices[ 0 ][ "message" ][ "content" ] # Get the reply from the API response
    return reply

if __name__ == "__main__":
    main()