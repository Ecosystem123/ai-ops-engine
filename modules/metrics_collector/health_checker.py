import os
import sys
import requests
import socket
import ssl
sys.path.append("../../configs")
from config_manager import *
def healthCheck():
  url = val['Clienttest']['url']
  res = requests.get(url)
  print(f"The status code: {res.status_code}")
  print(f"Response time: {res.elapsed.total_seconds()} ")
  addr = (val['Clienttest']['host'],443)
  ctx = ssl.create_default_context() 
  with socket.create_connection(addr) as sock:
      with ctx.wrap_socket(sock, server_hostname=addr[0]) as ssock:
          print(f"Certificate expiry: {ssock.getpeercert()['notAfter']}")
healthCheck()
