import unittest
from PromptGenerator import PromptGenerator

class TestPromptGenerator(unittest.TestCase):
    def setUp(self):
        self.app_description = "A blogging platform for amateur chefs"
        self.shared_dependencies = "User model, Post model, Comment model"
        self.filepaths_string = "/models/user.py, /models/post.py, /models/comment.py"
        self.prompt_generator = PromptGenerator(self.app_description, self.shared_dependencies, self.filepaths_string)

    def test_generate_prompt_for_code(self):
        filename = "/models/user.py"
        expected_start = "You are an AI developer who is trying to write a program that will generate code for the user based on their intent."
        expected_end = "Begin generating the code now.\n        "
        prompt = self.prompt_generator.generate_prompt_for_code(filename)
        self.assertTrue(prompt.startswith(expected_start))
        self.assertTrue(prompt.endswith(expected_end))
        self.assertIn(f"the file {filename}", prompt)
        self.assertIn(self.app_description, prompt)
        self.assertIn(self.shared_dependencies, prompt)
        self.assertIn(self.filepaths_string, prompt)
        print ( "prompt: ", prompt )

if __name__ == '__main__':
    unittest.main()
