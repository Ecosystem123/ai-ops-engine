import paramiko
import sys
import os
import logging
import logging_loki
sys.path.append("../../configs")
from config_manager import *
from func_timeout import func_timeout
def cloud_testing(a):
   obj = paramiko.SSHClient()
   obj.set_missing_host_key_policy(paramiko.AutoAddPolicy())
   obj.connect(val['Cloud1']['host'],port=22,username=val['Cloud1']['Username'],key_filename=val['Cloud1']['private_key'],timeout=4)
   stdin,stdout,stderr = obj.exec_command(a)
   output = stdout.read().decode()
   err = stderr.read().decode()
   obj.close()
   if err:
     print(err)  
   return output
s="journalctl -n 100"
timeout = 15
try:
 x = func_timeout(timeout,cloud_testing,args=(s,))
 handle = logging_loki.LokiHandler(
  url = val['Logging']['url'],
  tags = {"application": val['Logging']['tags']},
  auth = (val['Logging']['auth']['username'],val['Logging']['auth']['password']),
  version = "1",
 )
 logger = logging.getLogger("cloud-logs")
 logger.setLevel(logging.INFO)     
 handle.setLevel(logging.INFO)  
 logger.addHandler(handle)
 print("logging successful")
 if x:
  logger.info(x)
 else:
  logger.warning("cloud_testing returned empty output")
except Exception as e:
 print(e)
