Here is my source Python file that is causing the error:
```python
import sys
import time
from openai import OpenAI
from prompts import plan, specify_file_paths, generate_code_sync
from utils import generate_folder, write_file
# from smol_dev.prompts import plan, specify_file_paths, generate_code_sync
# from smol_dev.utils import generate_folder, write_file
import argparse

defaultmodel = "gpt-3.5-turbo-0613"

def main(prompt, generate_folder_path="generated", debug=False, model: str = defaultmodel):
    # create generateFolder folder if doesnt exist
    generate_folder(generate_folder_path)

    # plan shared_deps
    if debug:
        print("--------shared_deps---------")
    with open(f"{generate_folder_path}/shared_deps.md", "wb") as f:

        start_time = time.time()
        def stream_handler(chunk):
            f.write(chunk)
            if debug:
                end_time = time.time()

                sys.stdout.write("\r \033[93mChars streamed\033[0m: {}. \033[93mChars per second\033[0m: {:.2f}".format(stream_handler.count, stream_handler.count / (end_time - start_time)))
                sys.stdout.flush()
                stream_handler.count += len(chunk)

        stream_handler.count = 0
        stream_handler.onComplete = lambda x: sys.stdout.write("\033[0m\n") # remove the stdout line when streaming is complete

        shared_deps = plan(prompt, stream_handler, model=model)
    if debug:
        print(shared_deps)
    write_file(f"{generate_folder_path}/shared_deps.md", shared_deps)
    if debug:
        print("--------shared_deps---------")

    # specify file_paths
    if debug:
        print("--------specify_filePaths---------")
    file_paths = specify_file_paths(prompt, shared_deps, model=model)
    if debug:
        print(file_paths)
    if debug:
        print("--------file_paths---------")

    # loop through file_paths array and generate code for each file
    for file_path in file_paths:
        file_path = f"{generate_folder_path}/{file_path}"  # just append prefix
        if debug:
            print(f"--------generate_code: {file_path} ---------")

        start_time = time.time()
        def stream_handler(chunk):
            if debug:
                end_time = time.time()
                sys.stdout.write("\r \033[93mChars streamed\033[0m: {}. \033[93mChars per second\033[0m: {:.2f}".format(stream_handler.count, stream_handler.count / (end_time - start_time)))
                sys.stdout.flush()
                stream_handler.count += len(chunk)
        stream_handler.count = 0
        stream_handler.onComplete = lambda x: sys.stdout.write("\033[0m\n") # remove the stdout line when streaming is complete
        code = generate_code_sync(prompt, shared_deps, file_path, stream_handler, model=model)
        if debug:
            print(code)
        if debug:
            print(f"--------generate_code: {file_path} ---------")
        # create file with code content
        write_file(file_path, code)
        
    print("--------smol dev done!---------")


# for local testing
# python main.py --prompt "a simple JavaScript/HTML/CSS/Canvas app that is a one player game of PONG..." --generate_folder_path "generated" --debug True

if __name__ == "__main__":
    prompt = """
  a simple JavaScript/HTML/CSS/Canvas app that is a one player game of PONG. 
  The left paddle is controlled by the player, following where the mouse goes.
  The right paddle is controlled by a simple AI algorithm, which slowly moves the paddle toward the ball at every frame, with some probability of error.
  Make the canvas a 400 x 400 black square and center it in the app.
  Make the paddles 100px long, yellow and the ball small and red.
  Make sure to render the paddles and name them so they can controlled in javascript.
  Implement the collision detection and scoring as well.
  Every time the ball bouncess off a paddle, the ball should move faster.
  It is meant to run in Chrome browser, so dont use anything that is not supported by Chrome, and don't use the import and export keywords.
  """
    if len(sys.argv) == 2:
        prompt = sys.argv[1]
    else:
        parser = argparse.ArgumentParser()
        parser.add_argument("--prompt", type=str, required=True, help="Prompt for the app to be created.")
        parser.add_argument("--generate_folder_path", type=str, default="generated", help="Path of the folder for generated code.")
        parser.add_argument("--debug", type=bool, default=False, help="Enable or disable debug mode.")
        args = parser.parse_args()
        if args.prompt:
            prompt = args.prompt

    print(prompt)

    # Ensure args is defined even if sys.argv has only one argument
    if 'args' not in locals():
        class Args:
            generate_folder_path = "generated"
            debug = False
        args = Args()

    main(prompt=prompt, generate_folder_path=args.generate_folder_path, debug=args.debug)
```

Here is the error message:
```
(hp_agent_env) adamsl@DESKTOP-SHDBATI:~/developer/smol_dev$ python3 start_building.py
usage: start_building.py [-h] --prompt PROMPT [--generate_folder_path GENERATE_FOLDER_PATH] [--debug DEBUG]
start_building.py: error: the following arguments are required: --prompt
(hp_agent_env) adamsl@DESKTOP-SHDBATI:~/developer/smol_dev$ python3 start_building.py prompt.md
prompt.md
Error in plan method: name 'OpenAI' is not defined
Traceback (most recent call last):
  File "/home/adamsl/developer/smol_dev/start_building.py", line 111, in <module>
    main(prompt=prompt, generate_folder_path=args.generate_folder_path, debug=args.debug)
  File "/home/adamsl/developer/smol_dev/start_building.py", line 44, in main
    file_paths = specify_file_paths(prompt, shared_deps, model=model)
  File "/home/adamsl/developer/smol_dev/prompts.py", line 37, in specify_file_paths
    response = openai.ChatCompletion.create(
  File "/home/adamsl/hp_agent_env/lib/python3.10/site-packages/openai/lib/_old_api.py", line 39, in __call__
    raise APIRemovedInV1(symbol=self._symbol)
openai.lib._old_api.APIRemovedInV1:

You tried to access openai.ChatCompletion, but this is no longer supported in openai>=1.0.0 - see the README at https://github.com/openai/openai-python for the API.

You can run `openai migrate` to automatically upgrade your codebase to use the 1.0.0 interface.

Alternatively, you can pin your installation to the old version, e.g. `pip install openai==0.28`

A detailed migration guide is available here: https://github.com/openai/openai-python/discussions/742

(hp_agent_env) adamsl@DESKTOP-SHDBATI:~/developer/smol_dev$ pip3 install openai
Requirement already satisfied: openai in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (1.57.4)
Requirement already satisfied: sniffio in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (1.3.1)
Requirement already satisfied: httpx<1,>=0.23.0 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (0.28.1)
Requirement already satisfied: distro<2,>=1.7.0 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (1.9.0)
Requirement already satisfied: tqdm>4 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (4.67.1)
Requirement already satisfied: anyio<5,>=3.5.0 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (4.7.0)
Requirement already satisfied: typing-extensions<5,>=4.11 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (4.12.2)
Requirement already satisfied: jiter<1,>=0.4.0 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (0.8.2)
Requirement already satisfied: pydantic<3,>=1.9.0 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from openai) (2.10.3)
Requirement already satisfied: idna>=2.8 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from anyio<5,>=3.5.0->openai) (3.10)
Requirement already satisfied: exceptiongroup>=1.0.2 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from anyio<5,>=3.5.0->openai) (1.2.2)
Requirement already satisfied: httpcore==1.* in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from httpx<1,>=0.23.0->openai) (1.0.7)
Requirement already satisfied: certifi in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from httpx<1,>=0.23.0->openai) (2024.8.30)
Requirement already satisfied: h11<0.15,>=0.13 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from httpcore==1.*->httpx<1,>=0.23.0->openai) (0.14.0)
Requirement already satisfied: pydantic-core==2.27.1 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from pydantic<3,>=1.9.0->openai) (2.27.1)
Requirement already satisfied: annotated-types>=0.6.0 in /home/adamsl/hp_agent_env/lib/python3.10/site-packages (from pydantic<3,>=1.9.0->openai) (0.7.0)
(hp_agent_env) adamsl@DESKTOP-SHDBATI:~/developer/smol_dev$ python3 start_building.py prompt.md
prompt.md
Error in plan method: name 'OpenAI' is not defined
Traceback (most recent call last):
  File "/home/adamsl/developer/smol_dev/start_building.py", line 111, in <module>
    main(prompt=prompt, generate_folder_path=args.generate_folder_path, debug=args.debug)
  File "/home/adamsl/developer/smol_dev/start_building.py", line 44, in main
    file_paths = specify_file_paths(prompt, shared_deps, model=model)
  File "/home/adamsl/developer/smol_dev/prompts.py", line 37, in specify_file_paths
    response = openai.ChatCompletion.create(
  File "/home/adamsl/hp_agent_env/lib/python3.10/site-packages/openai/lib/_old_api.py", line 39, in __call__
    raise APIRemovedInV1(symbol=self._symbol)
openai.lib._old_api.APIRemovedInV1:

You tried to access openai.ChatCompletion, but this is no longer supported in openai>=1.0.0 - see the README at https://github.com/openai/openai-python for the API.

You can run `openai migrate` to automatically upgrade your codebase to use the 1.0.0 interface.

Alternatively, you can pin your installation to the old version, e.g. `pip install openai==0.28`

A detailed migration guide is available here: https://github.com/openai/openai-python/discussions/742

(hp_agent_env) adamsl@DESKTOP-SHDBATI:~/developer/smol_dev$
```
I tried to install openai but it still doesn't work.

Please help me fix this error.