import os
from openai import OpenAI
client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),
)

THREAD_ID = "thread_QNl4YyofnDmOparTPdIkKxx5"
ASSISTANT_ID = "asst_AucaMbkzXpymTiGJZyXUWXsx"

thread_message = client.beta.threads.messages.create(
  THREAD_ID,
  role="user",
  content="We are two players and don't have any characters yet. Can you make us a human fighter and an elven rogue?",
)

run = client.beta.threads.runs.create_and_poll(
  thread_id=THREAD_ID,
  assistant_id=ASSISTANT_ID
)

if run.status == 'completed': 
  messages = client.beta.threads.messages.list(
    thread_id=THREAD_ID
  )
  print(messages)
else:
  print(run.status)