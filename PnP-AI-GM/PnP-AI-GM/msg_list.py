import os
from openai import OpenAI
client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),
)

thread_messages = client.beta.threads.messages.list("thread_97CIE4JAVwqc9vhqDNgJwNJd")
print(thread_messages.data)