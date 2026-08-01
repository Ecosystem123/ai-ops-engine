import paramiko
from func_timeout import func_timeout
import json
def comm_ssh(a):
 data = {}
 obj = paramiko.SSHClient()
 obj.set_missing_host_key_policy(paramiko.AutoAddPolicy())
 obj.connect('10.199.99.241',port=22,username="rohan-sivadas",key_filename="/home/abhinandps/.ssh/testing",timeout=4)
 print("connected")
 stdin,stdout,stderr = obj.exec_command(a)
 err = stderr.read().decode()
 if err:
   data.update({
     "error": err,
     "exit-code": 1
   })
 else:
   data.update({
     "command": stdout.read().decode(),
     "exit-code": 0
   })
 
 return data
s=input("Enter the command: ")
timeout = 15
try:
 print(func_timeout(timeout,comm_ssh,args=(s,)))
except Exception as e:
 print("command timed out")
 print(e)
