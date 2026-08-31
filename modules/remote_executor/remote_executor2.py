import paramiko
import sys
import os
sys.path.append("../../configs")
from config_manager import *
from func_timeout import func_timeout
def cloud_testing(a):
   obj = paramiko.SSHClient()
   obj.set_missing_host_key_policy(paramiko.AutoAddPolicy())
   obj.connect(val['CloudGpu']['host'],port=22,username=val['CloudGpu']['Username'],key_filename=val['CloudGpu']['private_key'],timeout=4)
   stdin,stdout,stderr = obj.exec_command(a)
   output = stdout.read().decode()
   err = stderr.read().decode()
   if err:
     print(err)  
   else:
    print(output)
s=input("Enter the command: ")
timeout = 15
try:
 print(func_timeout(timeout,cloud_testing,args=(s,)))
except Exception as e:
 print(e)
