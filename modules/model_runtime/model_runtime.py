import paramiko
import sys
import os
import time
sys.path.append("../../configs")
from config_manager import *
from func_timeout import func_timeout
def run_model(a):
    obj = paramiko.SSHClient()
    obj.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    obj.connect(
        val['CloudGpu']['host'],
        port=val['CloudGpu']['port'],
        username=val['CloudGpu']['username'],
        key_filename=val['CloudGpu']['key_filename'],
        timeout=50,
        allow_agent=False,
        look_for_keys=False
    ) 
    stdin, stdout, stderr = obj.exec_command(a)
    output = stdout.read().decode()
    err = stderr.read().decode()
    if err:
        print(err)
    else:
        print(output)
    obj.close()
    return output
s = "nohup bash -c 'pip install pyairports && /usr/bin/python3 -m vllm.entrypoints.openai.api_server --model TinyLlama/TinyLlama-1.1B-Chat-v1.0 --host 0.0.0.0 --port 8000' > /tmp/vllm.log 2>&1 & echo Ready"
timeout = 180
try:
    func_timeout(timeout, run_model, args=(s,))
except Exception as e:
    print(e)
time.sleep(60)
test_cmd = '''curl --max-time 20 http://localhost:8000/v1/chat/completions -H "Content-Type: application/json" -d '{"model": "TinyLlama/TinyLlama-1.1B-Chat-v1.0", "messages": [{"role": "user", "content": "Say hi in 3 words"}]}' '''
print(run_model(test_cmd))
