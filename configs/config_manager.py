import yaml
from pathlib import Path
config = Path(__file__).resolve().parent /"config_manager.yaml"
with open(config,'r') as file:
 val = yaml.safe_load(file)
if __name__ == "__main__":
  print(val)
