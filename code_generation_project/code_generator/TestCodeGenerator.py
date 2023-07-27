import unittest
from unittest.mock import Mock, patch
from CodeGenerator import CodeGenerator

class TestCodeGenerator(unittest.TestCase):
    @patch("prompt_generator.PromptGenerator")
    @patch("openai_api_service.OpenAIAPIService")
    def test_generate_code_for_file(self, MockOpenAIAPIService, MockPromptGenerator):
        # Arrange
        mock_prompt = "Generated prompt for code."
        mock_response = Mock()
        mock_response.choices = [Mock(text="Generated code.")]
        MockPromptGenerator.return_value.generate_prompt_for_code.return_value = mock_prompt
        MockOpenAIAPIService.return_value.call_gpt3.return_value = mock_response
        code_generator = CodeGenerator(MockPromptGenerator.return_value, MockOpenAIAPIService.return_value)
        expected_filename = "test.py"
        expected_code = "Generated code."

        # Act
        actual_filename, actual_code = code_generator.generate_code_for_file(expected_filename)

        # Assert
        self.assertEqual(expected_filename, actual_filename)
        self.assertEqual(expected_code, actual_code)
        MockPromptGenerator.return_value.generate_prompt_for_code.assert_called_once_with(expected_filename)
        MockOpenAIAPIService.return_value.call_gpt3.assert_called_once_with(mock_prompt)

if __name__ == "__main__":
    unittest.main()
