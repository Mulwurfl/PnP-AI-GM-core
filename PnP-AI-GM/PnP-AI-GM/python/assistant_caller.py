import os
from openai import OpenAI
client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),
)
  
ASSISTANT_ID = "asst_AucaMbkzXpymTiGJZyXUWXsx"

def send_msg(x):
    return "Successfully Processed anew: " + x

def read_msg(x):
    return ""



