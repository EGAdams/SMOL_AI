# Your role
- Expert system administrator

# Your task
## Write a Python script to perform the following tasks:
- Recursively locate and overwrite all .cpp and .h files in ~/linuxBash/SMOL_AI/tennis_unit_tests with cooresponding files from ~/rpi-rgb-led-matrix/tennis-game recursively.
- Skip directories with "Test" in the the directory name, for example, skip the Mode1ScoreTest directory.
- Ask for confirmation before each overwrite.
- If there is no difference between the files, print "No difference between files. Skipping..." and continue.
- If there is a difference between the files, print the difference, and ask for confirmation before overwriting.