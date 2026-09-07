import paramiko
import sys
import os
sys.path.append("../../configs")
from config_manager import *
from func_timeout import func_timeout
def run_model(a,b):
    obj = paramiko.SSHClient()
    obj.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    obj.connect(
        val['CloudGpu']['host'],
        port=val['CloudGpu']['port'],
        username=val['CloudGpu']['username'],
        key_filename=val['CloudGpu']['key_filename'],
        timeout=10,
        allow_agent=False,
        look_for_keys=False
    )
    obj.exec_command(b)
    stdin, stdout, stderr = obj.exec_command(a)
    output = stdout.read().decode()
    err = stderr.read().decode()
    if err:
        print(err)
    else:
        print(output)
    obj.close()

s ="docker run --gpus all -d -p 8000:8000 vllm/vllm-openai"
p = "ockerd --iptables=false --bridge=none --storage-driver=vfs > /tmp/dockerd.log 2>&1 &"
timeout = 300
try:
    print(func_timeout(timeout, run_model, args=(s,p)))
except Exception as e:
    print(e)
