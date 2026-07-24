#commonlog.py
import logging
from pathlib import Path
def createLog(s):
  x = Path(__file__).parent/ f"{s}.txt"
  logging.basicConfig(filename = x , level = logging.DEBUG, format='{"time":"%(asctime)s","level":"%(levelname)s","message":"%(message)s"}')
  print("log file created")
