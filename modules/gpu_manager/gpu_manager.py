from pynvml import *
nvmlInit()
print(f"No of gpu's present: {nvmlDeviceGetCount()}")
for i in range(nvmlDeviceGetCount()):
 handle = nvmlDeviceGetHandleByIndex(i)
 mem=nvmlDeviceGetMemoryInfo(handle)
 print(f"Device name: {nvmlDeviceGetName(handle)}")
 print(f"Memory utilised is: total={mem.total / 1e9:.2f} GB,free={mem.free / 1e9:.2f} GB,used={mem.used / 1e9:.2f} GB")
 print(f"Power consumed is: {nvmlDeviceGetPowerUsage(handle) / 1000:.2f} W")
 print(f"Temperature is: {nvmlDeviceGetTemperature(handle,NVML_TEMPERATURE_GPU)} degrees")
 print(f"Driver version: {nvmlSystemGetDriverVersion()}")
