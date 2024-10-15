import os
import json
from openai import OpenAI
client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),
)

ASSISTANT_ID = "asst_ozBMqP2nHlXqp4fsOsRmumm3"
THREAD_ID = "thread_h1xZrDv8Ro8aaTY4heyptb4c"
MODEL_ID = "gpt-4o-mini-2024-07-18"

def send_msg(x,y):
    thread_message = client.beta.threads.messages.create(
        thread_id=x,
        role="user",
        content=y,
    )
    return thread_message

def run(x,y):
    run = client.beta.threads.runs.create(
        thread_id=x,
        assistant_id=ASSISTANT_ID,
        model=MODEL_ID,
        additional_instructions=y
    )
    return run.id

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
            value = None  # or some default value or handling

        # Repackage into a simpler dictionary
        simplified_message = {
            "id": message_id,
            "role": role,
            "value": value
        }
        simplified_messages.append(simplified_message)

    return json.dumps(simplified_messages)

def check_thread(x):
    my_thread = client.beta.threads.retrieve(x)
    return my_thread.id

#print(send_msg(THREAD_ID,"Begin section. Trigger for next section is going or looking into the cellar. $$: Ok, let's start the game"))
#print("\n")
#print(run(THREAD_ID,""))
print(get_msg_list(THREAD_ID,100))
#print(check_thread("thread_T83W9eKltTVi3vTQdiLeYBOe"))