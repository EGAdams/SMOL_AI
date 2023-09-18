import os
import difflib
import shutil

def get_difference(file1, file2):
    """
    Return the difference between two files as a string.
    """
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        diff = difflib.ndiff(f1.readlines(), f2.readlines())
        return '\n'.join(list(diff))

def confirm_action(message):
    """
    Ask the user for confirmation based on the provided message.
    """
    while True:
        user_input = input(f"{message} (y/n): ").lower()
        if user_input in ['y', 'n']:
            return user_input == 'y'

def overwrite_files(src_dir, dest_dir):
    """
    Recursively traverse the source directory and overwrite files in the destination directory.
    """
    for root, dirs, files in os.walk(src_dir):
        if "Test" in os.path.basename(root):
            continue

        for file in files:
            if "Test" in file:
                continue
            if file.endswith(('.cpp', '.h')):
                src_file = os.path.join(root, file)
                dest_file = os.path.join(dest_dir, os.path.relpath(src_file, src_dir))

                if os.path.exists(dest_file):
                    difference = get_difference(src_file, dest_file)
                    
                    if difference:
                        print(f"Difference found for {file}:")

                        # if confirm_action("Do you want to overwrite?"):
                        #     shutil.copy(src_file, dest_file)
                        print( "overwriting... " )
                        shutil.copy(src_file, dest_file)
                    else:
                        print(f"No difference between {file}. Skipping...")
                else:
                    if confirm_action(f"{file} doesn't exist in destination. Copy it?"):
                        os.makedirs(os.path.dirname(dest_file), exist_ok=True)
                        shutil.copy(src_file, dest_file)

# Define the source and destination directories
src_directory = "/home/adamsl/rpi-rgb-led-matrix/tennis-game"
dest_directory = "/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests"

# Call the function to start the overwriting process (Note: This is a demonstration and will not run in this environment)
overwrite_files(src_directory, dest_directory)

# Displaying the main function for review
# overwrite_files
