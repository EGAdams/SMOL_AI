import openai

class OpenAIAPIService:
    def __init__(self, api_key, engine="text-davinci-002"):
        self.api_key = api_key
        self.engine = engine
        openai.api_key = self.api_key

    def call_gpt3(self, prompt, max_tokens):
        """Call the OpenAI GPT-3 API with the given prompt and max tokens."""
        try:
            response = openai.Completion.create(engine=self.engine, prompt=prompt, max_tokens=max_tokens)
            return response
        except Exception as e:
            print(f"An error occurred: {e}")
            return None