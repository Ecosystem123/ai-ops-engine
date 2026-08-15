from prometheus_client import start_http_server,Gauge
import time
val = Gauge('engine_operation_total','counts the no of docker client operations', ['method', 'endpoint'])
val1 = Gauge('kubernetics','count the no of kubernetics operations', ['method', 'endpoint'])
scrapes = Gauge('engine_scrapes_total','number of times exporter metrics were updated')
start_http_server(8000)
while True:
 file = open("variable.txt","r")
 s = file.read().splitlines()
 k = list(map(int,s))
 val.labels(method='GET',endpoint='/metrics').set(k[0])
 val1.labels(method='GET',endpoint='/metrics').set(k[1])
 scrapes.inc()
 time.sleep(5)
