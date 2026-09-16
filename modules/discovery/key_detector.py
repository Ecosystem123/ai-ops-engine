import os
import sys
import re
sys.path.append("../../configs")
from key_manager import *
keys = val['User1']['key']
for key in keys:
      if "AKIA" in key or "ASIA" in key:
       print("The key provided is AWS key")
      elif "AIza" in key:
       print("The key provided is GCP key")
      elif "dop_v1_" in key:
       print("The key provided is DigitalOcean key")
      else:
       regex = r'^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$'
       if re.match(regex, key):
        print("The key provided is Microsoft Azure key")
       else:
        print("Unknown provider")
