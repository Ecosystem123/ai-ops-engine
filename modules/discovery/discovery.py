import yaml
from pathlib import Path
from func_timeout import func_timeout,FunctionTimedOut
import paramiko
val = Path(__file__).parents[2] /"configs/config_manager.yaml"
with open(val,'r') as file:
 x = yaml.safe_load(file)
print(x)
def connectionCheck(x):
 t = x['remote_executor']['port']
 t1 = x['remote_executor']['ipv4']
 t2 = x['remote_executor']['username']
 t3 = x['remote_executor']['key_filename']
 obj = paramiko.SSHClient()
 try:
  obj.connect(t1,port=t,username=t2,key_filename=t3,timeout=4)
  print(obj.get_transport().is_active())
 except:
  print("Connection not active")
time = 15
try:
 func_timeout(time,connectionCheck,args=(x,))
except FunctionTimedOut:
 print("time exceeded")
 print("Try again")
