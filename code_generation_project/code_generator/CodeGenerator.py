from typing import Tuple
# import the PromptGenerator class from the file in the parent directory called prompt_generator
from  prompt_generator.PromptGenerator import PromptGenerator


class CodeGenerator:
    def __init__( self, prompt_generator: PromptGenerator, api_service: OpenAIAPIService ):
        self.prompt_generator = prompt_generator
        self.api_service = api_service

    def generate_code_for_file( self, filename: str ) -> Tuple[str, str]:
        prompt = self.prompt_generator.generate_prompt_for_code( filename )
        response = self.api_service.call_gpt3( prompt )
        # Extract the choices from the response and return the first one's text.
        return filename, response.choices[ 0 ].text.strip()
