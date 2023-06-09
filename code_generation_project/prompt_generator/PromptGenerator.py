class PromptGenerator:
    def __init__(self, app_description, shared_dependencies, filepaths_string):
        self.app_description = app_description
        self.shared_dependencies = shared_dependencies
        self.filepaths_string = filepaths_string

    def generate_prompt_for_code(self, filename):
        # Create the initial part of the prompt with the AI developer context, the app description, 
        # the filepaths, and the shared dependencies
        prompt = f"""You are an AI developer who is trying to write a program that will generate code for the user based on their intent.

        The app is: {self.app_description}

        The files we have decided to generate are: {self.filepaths_string}

        The shared dependencies (like filenames and variable names) we have decided on are: {self.shared_dependencies}

        Only write valid code for the given filepath and file type, and return only the code.
        Do not add any other explanation, only return valid code for that file type."""

        # Add a user prompt instructing the model to generate code for a specific file
        prompt += f"""
        We have broken up the program into per-file generation.
        Now your job is to generate only the code for the file {filename}.
        Make sure to have consistent filenames if you reference other files we are also generating.

        Remember that you must obey 3 things:
        - you are generating code for the file {filename}
        - do not stray from the names of the files and the shared dependencies we have decided on
        - MOST IMPORTANT OF ALL - the purpose of our app is {self.app_description} - every line of code you generate must be valid code. Do not include code fences in your response, for example.

        Bad response:
        ```javascript
        console.log("hello world")
        ```

        Good response:
        console.log("hello world")
        
        Begin generating the code now.
        """

        return prompt

    def generate_prompt_for_file(self, file_structure):
        # This method is not used in the original methods so we leave it as it is
        prompt = f"You are an AI developer who is trying to write a program that will generate code {self.app_description}\n\nFile Structure:\n{file_structure}\n\n"
        prompt += "File Content:\n"
        return prompt
