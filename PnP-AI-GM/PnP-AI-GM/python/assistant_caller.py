import os
import json
from openai import OpenAI
client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),
)
  
ASSISTANT_ID = "asst_pJZCD4IOf0rlXmhVBT5R0VDL"
THREAD_ID = ""
MODEL_ID = "gpt-4o"

def test(x,y):
    THREAD_ID = x
    return "Successfully Processed anew: " + y

def send_msg(x,y):
    thread_message = client.beta.threads.messages.create(
        thread_id=x,
        role="user",
        content=y
    )
    return 1

def send_msg_as_gm(x,y,a): # a is the name of the file to use in append_file(), leave null to skip append
    if a != None:
        x = append_file(x,a)

    thread_message = client.beta.threads.messages.create(
        thread_id=xx,
        role="assistant",
        content=y
    )
    return 1

def append_file(text, filename):
    c = text.find("$$:")
    if c == -1:
        raise Exception("Textual separator missing in message.")
    file = open(filename)
    text = text[:c] + "Information from file \" " + filename[:-4] + "\":\n" + file.read() + "\n" + text[c:]
    file.close()
    return text

def send_msg_fs(x,y,z):
    thread_message = client.beta.threads.messages.create(
        thread_id=x,
        role="user",
        content=y,
        attachments=[{
            "file_id": z,
            "tools": [{"type": "file_search"}]
            }]
    )
    return 1

def get_msg_list(x,y):
    thread_messages = client.beta.threads.messages.list(
        thread_id=x,
        limit=y,
        order="desc"
    )

    simplified_messages = []
    for message in thread_messages.data:
        message_id = message.id
        role = message.role
        # Navigate through the nested structure to get the 'value'
        if message.content and message.content[0].type == "text":
            value = message.content[0].text.value
        else:
            value = ""  # or some default value or handling

        # Repackage into a simpler dictionary
        simplified_message = {
            "id": message_id,
            "role": role,
            "value": value
        }
        simplified_messages.append(simplified_message)

    return json.dumps(simplified_messages)

def run(x,y):
    run = client.beta.threads.runs.create(
        thread_id=x,
        assistant_id=ASSISTANT_ID,
        model=MODEL_ID,
        additional_instructions=y
    )
    return run.id

def run_with_fs(x,y):
    run = client.beta.threads.runs.create(
        thread_id=x,
        assistant_id=ASSISTANT_ID,
        model=MODEL_ID,
        tools=[{"type": "file_search"}],
        additional_instructions=y
    )
    return run.id

def create_thread():
    new_thread = client.beta.threads.create()
    return new_thread.id

def retrieve_thread(x):
    my_thread = client.beta.threads.retrieve(x)
    return my_thread.id

def get_run(x,y):
    run = client.beta.threads.runs.retrieve(
        thread_id=x,
        run_id=y
    )
    return run.status


