#main.py
import logging
import sys
sys.path.append("../data/logs/enginelog_python")
import commonlog
def logHandle():
 t = sys.argv[0].removesuffix(".py")
 commonlog.createLog(t)
 log = logging.getLogger();
 x=10/0
 log.info("The porgram started. Working fine")
if __name__ == "__main__":
 try:
  logHandle()
 except:
   log = logging.getLogger();
   log.error("Something wrong")
