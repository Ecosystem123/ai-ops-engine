import requests
from prometheus_client.parser import text_string_to_metric_families
try:
  k = requests.get('http://localhost:9835/metrics')
  data = {}
  k1 = k.text
  for i in  text_string_to_metric_families(k1):
   for j in i.samples:
     if j.name == 'nvidia_smi_memory_used_bytes':
       print("nvidia_smi_memory_used_bytes:",j.value)
       data["nvidia_smi_memory_used_bytes"] = j.value
     if j.name == 'nvidia_smi_memory_total_bytes':
       print("nvidia_smi_memory_total_bytes:",j.value)
       data["nvidia_smi_memory_total_bytes"] = j.value
     if j.name == 'nvidia_smi_temperature_gpu':
       print("nvidia_smi_temperature_gpu:",j.value)
       data["nvidia_smi_temperature_gpu"] = j.value
     if j.name == 'nvidia_smi_power_draw_watts':
       print("nvidia_smi_power_draw_watts:",j.value)
       data["nvidia_smi_power_draw_watts"] = j.value
except Exception as e:
 print(e)
