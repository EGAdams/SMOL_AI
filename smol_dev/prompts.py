import asyncio
import re
import time
import openai
import logging
from tenacity import retry, stop_after_attempt, wait_random_exponential
from typing import List, Optional, Callable, Any

logger = logging.getLogger(__name__)

SMOL_DEV_SYSTEM_PROMPT = """
You are a top-tier AI developer who is trying to write a program that will generate code for the user based on their intent.
Do not leave any todos, fully implement every feature requested.

When writing code, add comments to explain what you intend to do and why it aligns with the program plan and specific instructions from the original prompt.
"""

def specify_file_paths(prompt: str, plan: str, model: str = 'gpt-3.5-turbo-0613') -> List[str]:
    functions = [
        {
            "name": "file_paths",
            "description": "Construct a list of file paths based on the provided files to edit.",
            "parameters": {
                "type": "object",
                "properties": {
                    "files_to_edit": {
                        "type": "array",
                        "items": {"type": "string"},
                        "description": "List of file paths to edit."
                    }
                },
                "required": ["files_to_edit"]
            }
        }
    ]

    response = openai.ChatCompletion.create(
        model=model,
        temperature=0.7,
        functions=functions,
        function_call={"name": "file_paths"},
        messages=[
            {"role": "system", "content": f"{SMOL_DEV_SYSTEM_PROMPT}\nGiven the prompt and the plan, return a list of strings corresponding to the new files that will be generated."},
            {"role": "user", "content": f"I want a: {prompt}"},
            {"role": "user", "content": f"The plan we have agreed on is: {plan}"},
        ],
    )

    return response["choices"][0]["message"]["function_call"]["arguments"]["files_to_edit"]

GPT_MODEL = "gpt-3.5-turbo-0125"

def plan(prompt: str, 
         stream_handler: Optional[Callable[[bytes], None]] = None, 
         model: str = GPT_MODEL, 
         extra_messages: List[Any] = []):

    messages = [
        {"role": "system", "content": f"{SMOL_DEV_SYSTEM_PROMPT}\nWrite a plan using GitHub Markdown syntax."},
        {"role": "user", "content": f"The app prompt is: {prompt}"},
        *extra_messages
    ]

    try:
        client = OpenAI()  # Create OpenAI client
        response = client.chat.completions.create(
            model=model,
            messages=messages
        )
        
        print("Received response from OpenAI")
        response_message = response.choices[0].message.content
        
        if stream_handler:
            try:
                stream_handler(response_message.encode("utf-8"))
            except Exception as err:
                logger.error(f"stream_handler error: {err}")

        return response_message

    except Exception as e:
        logger.error(f"Error in plan method: {e}")
        return ""

@retry(wait=wait_random_exponential(min=1, max=60), stop=stop_after_attempt(6))
async def generate_code(prompt: str, plan: str, current_file: str, stream_handler: Optional[Callable[Any, Any]] = None, model: str = 'gpt-3.5-turbo-0613') -> str:
    completion = openai.ChatCompletion.acreate(
        model=model,
        temperature=0.7,
        messages=[
            {"role": "system", "content": f"{SMOL_DEV_SYSTEM_PROMPT}\nGenerate code for the file: {current_file}."},
            {"role": "user", "content": f"The plan we have agreed on is: {plan}"},
            {"role": "user", "content": f"The app prompt is: {prompt}"},
        ],
        stream=True,
    )

    collected_messages = []
    async for chunk in completion:
        chunk_message = chunk["choices"][0]["delta"]
        if chunk["choices"][0]["finish_reason"] is None:
            collected_messages.append(chunk_message)
            if stream_handler:
                try:
                    stream_handler(chunk_message["content"].encode("utf-8"))
                except Exception as err:
                    logger.error("stream_handler error:", err)

    code_file = "".join([m.get("content", "") for m in collected_messages])
    pattern = r"```[\w\s]*\n([\s\S]*?)```"
    code_blocks = re.findall(pattern, code_file, re.MULTILINE)
    return code_blocks[0] if code_blocks else code_file

def generate_code_sync(prompt: str, plan: str, current_file: str, stream_handler: Optional[Callable[Any, Any]] = None, model: str = 'gpt-3.5-turbo-0613') -> str:
    loop = asyncio.get_event_loop()
    return loop.run_until_complete(generate_code(prompt, plan, current_file, stream_handler, model))
