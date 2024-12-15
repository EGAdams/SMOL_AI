import sys

from smol_dev.prompts import plan, specify_file_paths, generate_code_sync
from smol_dev.utils import generate_folder, write_file
from smol_dev.main import main
import argparse




# for local testing
# python main.py --prompt "a simple JavaScript/HTML/CSS/Canvas app that is a one player game of PONG..." --generate_folder_path "generated" --debug True

if __name__ == "__main__":
    prompt = """
  
  """
    if len(sys.argv) == 2:
        prompt = sys.argv[1]
    else:
        
        parser = argparse.ArgumentParser()
        parser.add_argument("--prompt", type=str, help="Prompt for the app to be created.")
        parser.add_argument("--model", type=str, default="gpt-3.5-turbo", help="model to use. can also use gpt-3.5-turbo-0613")
        parser.add_argument("--generate_folder_path", type=str, default="generated", help="Path of the folder for generated code.")
        parser.add_argument("--debug", type=bool, default=False, help="Enable or disable debug mode.")
        args = parser.parse_args()
        if args.prompt:
            prompt = args.prompt

    # read file from prompt if it ends in a .md filetype
    # if len(prompt) < 100 and prompt.endswith(".md"):
    #     with open(prompt, "r") as promptfile:
    #         prompt = promptfile.read()
    
    with open( "tennis_ont_prompt.md", "r") as promptfile:
            prompt = promptfile.read()

    print(prompt)
        
    main(prompt=prompt, generate_folder_path=args.generate_folder_path, debug=args.debug, model=args.model)
