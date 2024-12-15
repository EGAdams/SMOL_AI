import os
from time import sleep
DEFAULT_DIR             = "/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/"
OBJECT_OF_INTEREST      = "PinInterface"
TURBO_MODEL             = "gpt-3.5-turbo"

def read_file(filename):
    with open(filename, "r" ) as file:
        return file.read()

def walk_directory( directory ):
    files_to_read = [
    "TieBreaker.h", "TieBreaker.cpp",
    "Arduino.h", "Arduino.cpp",
    "GameLeds.h", "GameLeds.cpp",
    "GameTimer.h", "GameTimer.cpp",
    "PointLeds.h", "PointLeds.cpp",
    "PinInterface.h", "PinInterface.cpp",
    "Player.h", "Player.cpp",
    "ServeLeds.h", "ServeLeds.cpp",
    "SetLeds.h", "SetLeds.cpp",
    "WatchTimer.h", "WatchTimer.cpp",
    "WinSequences.h", "WinSequences.cpp",
    "Undo.h", "Undo.cpp",
    "Inputs.h", "Inputs.cpp" ]
    
    code_contents = {}
    all_text = ""
    for root, dirs, files in os.walk(directory):
        for file in files:
            #if any(file.endswith(ext) for ext in image_extensions):
            # if the file is in the files_to_read list
            if file in files_to_read:
                try:
                    relative_filepath = os.path.relpath(
                        os.path.join(root, file), directory
                    )
                    print( "Reading file: ", relative_filepath )
                    code_contents[relative_filepath] = read_file(
                        os.path.join(root, file)
                    )
                    # add to all_text
                    all_text += code_contents[relative_filepath]
                except Exception as e:
                    code_contents[
                        relative_filepath
                    ] = f"Error reading file {file}: {str(e)}"
                    
    return all_text
    
# return code_contents
# main
def main():
    directory_to_walk = DEFAULT_DIR  # + OBJECT_OF_INTEREST
    # prompt          = read_file( DEFAULT_DIR + "make_error_prompt.md" ) # the error message
    directory       = directory_to_walk           # the object's directory
    # model           = TURBO_MODEL                                       # the model to use
    code_contents   = walk_directory( directory ) # code_contents will contain all of the code.
    
    # put code_contents into a file called tennis_files.cpp
    with open( "tennis_files.cpp", "w" ) as file:
        file.write( code_contents )
    
    # context         = "\n".join( f"{path}:\n{contents}" for path, contents in code_contents.items())

if __name__ == "__main__":
    main()