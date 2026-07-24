import logging
import commonlog
def test():
 logging.info("program started with no problems")
 print("Starting api")
 print("working fine")
if __name__ == "__main__":
 try:
  test()
 except Exception:
  logging.critical("program crashed")
  logging.exception("Details of the crash")
 
