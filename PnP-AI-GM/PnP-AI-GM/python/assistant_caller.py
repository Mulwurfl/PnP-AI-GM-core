import os
from openai import OpenAI
client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),
)
  
ASSISTANT_ID = "asst_AucaMbkzXpymTiGJZyXUWXsx"
THREAD_ID = ""
MODEL_ID = "gpt-4o-2024-05-13"

def test(x,y):
    THREAD_ID = x
    return "Successfully Processed anew: " + y

def send_msg(x,y):
    thread_message = client.beta.threads.messages.create(
        thread_id=x,
        role="user",
        content=y,
    )
    return 1

def get_msg_list(x,y):
    thread_messages = client.beta.threads.messages.list(
        thread_id=x,
        limit=y,
        order=desc
    )
    return thread_messages.data

def run(x,y):
    run = client.beta.threads.runs.create(
        thread_id=x,
        assistant_id=ASSISTANT_ID,
        model=MODEL_ID,
        additional_instructions=y
    )
    return 1

def run_with_fs(x,y):
    run = client.beta.threads.runs.create(
        thread_id=x,
        assistant_id=ASSISTANT_ID,
        model=MODEL_ID,
        tools=[{"type": "file_search"}],
        additional_instructions=y
    )
    return 1

def create_thread():
    new_thread = client.beta.threads.create()
    return new_thread



