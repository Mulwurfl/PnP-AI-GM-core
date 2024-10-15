import os
from openai import OpenAI
client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),
)

thread_message = client.beta.threads.messages.create(
  "thread_test123",
  role="user",
  content="How does AI work? Explain it in simple terms.",
)
print(thread_message)