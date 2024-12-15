import unittest
from openai.api_resources.completion import Completion
from OpenAIAPIService import OpenAIAPIService # import OpenAIAPIService from local file
from openai.api_resources.abstract.api_resource import APIResource
from openai.openai_object import OpenAIObject

class TestOpenAIAPIService(unittest.TestCase):
    def setUp(self):
        self.service = OpenAIAPIService( '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' )

    def test_call_gpt3(self):
        print( "translating 'Hello, world!' to French..." )
        response = self.service.call_gpt3('Translate the following English text to French: "Hello, world!"', 60)
        print( "response:", response.choices[0].text )
        # Check that the response is an instance of the OpenAIObject class, which means the API call was successful.
        self.assertIsInstance(response, OpenAIObject)
        # Check that the response has an 'id' attribute, which is present in successful responses.
        self.assertTrue(hasattr(response, 'id'))

if __name__ == '__main__':
    unittest.main()