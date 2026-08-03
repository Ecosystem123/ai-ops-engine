# AI Infrastructure & Cloud Ops Engine — 60 Day Roadmap

A strictly day-by-day engineering roadmap. Every day has a specific goal, concept, and concrete deliverable that adds a permanent file or feature to the engine.

---

## Phase 1: Foundation & Core (Days 1–24)

| Day | Task | Details | Deliverable |
|---|---|---|---|
| 1 | Initialize Project Repository | Create the Git repo. Set up root folders: `core/` (C++), `modules/` (Python), `scripts/`, `tests/`, `configs/`. Basic `CMakeLists.txt` and `pyproject.toml`. | A structured repo that compiles a "Hello Engine" C++ binary and runs a "Hello Module" Python script. |
| 2 | Setup Logging System | Central logging utility in C++ (`spdlog`) and Python (`logging`), writing structured JSON logs to a shared `logs/` directory. | All future modules call `EngineLogger::info("...")` instead of `cout`. |
| 3 | Build Docker API HTTP Client (C++) | `DockerClient` class using `libcurl` to call the Docker Unix socket (`/var/run/docker.sock`). Implement `ListContainers()`. | Binary prints running containers on the local machine. |
| 4 | Inspect Container Details | Extend `DockerClient` with `InspectContainer(id)` — image, entrypoint, env vars, port bindings, resource limits. | JSON dump of a container's full configuration. |
| 5 | Start and Stop Containers | Add `StartContainer(id)` / `StopContainer(id)`. Handle HTTP codes (204, 304, 404). | Engine can remotely restart a container via code. |
| 6 | Subscribe to Docker Events | Streaming GET to `/events`. Parse event stream line-by-line (start, die, stop, destroy) to the logger. | Background thread monitoring Docker events in real-time. |
| 7 | Implement SSH Connection Manager (Python) | `remote_executor.py`, `SSHClient` class using `paramiko`. Key-based auth, `echo "hello"` test. | Reusable SSH class handling auth and command execution. |
| 8 | Remote Command Execution | Extend `SSHClient` for long-running commands with timeouts; capture `stdout`/`stderr`; return structured result object. | Can run `nvidia-smi` on a remote server and get output back. |
| 9 | Create Configuration Manager | `config_manager.py` loads `configs/engine_config.yaml`. Global singleton for `ssh_key_path`, `docker_socket_path`, `client_inventory`. | Single source of truth for all module settings. |
| 10 | Implement Infrastructure Discovery | `discovery.py` reads clients from YAML, TCP-pings port 22 on each. | Reachable/unreachable status dictionary. |
| 11 | Kubernetes API Connection | `K8sClient` class, reads `~/.kube/config`, `ListPods(namespace)`. | Prints all pods in the "default" namespace. |
| 12 | Fetch Pod Details | Extend `K8sClient`: pod conditions, restart counts, node hostname. | Pod health report. |
| 13 | Metrics Exporter | `exporter.py` runs a `prometheus_client` HTTP server, exposes `engine_scrapes_total`. | `/metrics` endpoint on port 8000. |
| 14 | Pull Remote Metrics | `metrics_collector.py` GETs a remote `/metrics` endpoint, parses Prometheus text format for GPU memory values. | Remote metrics stored in memory. |
| 15 | Centralized Logging (Loki) | `log_agent.py` pulls remote logs via SSH `tail -n 100`, pushes to Loki via HTTP. | Remote logs land in Loki. |
| 16 | NVML Init | `gpu_manager.py`, `nvmlDeviceGetCount()`. | Prints total local GPUs. |
| 17 | Collect GPU Stats | Extend `gpu_manager.py`: temp, power, memory used/total, utilization %, driver version. | GPU health dict. |
| 18 | Deploy vLLM | `model_runtime.py` pulls `vllm/vllm-openai` image, runs with `--gpus all`, port 8000. | One function deploys an inference server. |
| 19 | Health Check Model Runtime | GET `http://localhost:8000/health`, wait for 200 or timeout at 60s. | Deploy function confirms readiness. |
| 20 | AWS SDK Setup | Install `boto3`, write `aws_client.py`, load creds from `secrets_manager.py`, `ListEC2Instances()`. | Engine lists a client's running EC2 instances. |
| 21 | AWS Full Inventory | Extend `aws_client.py`: `ListEBSVolumes()`, `ListLoadBalancers()`, `ListRDSInstances()`, `ListS3Buckets()`. | JSON dump of a client's full AWS footprint. |
| 22 | GCP SDK Setup | Install `google-cloud-compute`, write `gcp_client.py`, `ListInstances()` for Compute Engine. | Same instance-list capability on GCP. |
| 23 | Azure SDK Setup | Install `azure-mgmt-compute`, write `azure_client.py`, `ListVMs()`. | Same on Azure — three providers now supported. |
| 24 | Unified CloudResource Model | `CloudResource` dataclass (`provider`, `resource_id`, `type`, `region`, `tags`, `cost_estimate`); adapters so AWS/GCP/Azure clients all return this shape. | One consistent data format regardless of cloud provider. |

---

## Phase 2: Diagnosis, Auto-Heal & GPU Cost (Days 25–39)

| Day | Task | Details | Deliverable |
|---|---|---|---|
| 25 | Connect Grafana to Prometheus | Script/API call adding Prometheus as a Grafana data source. | Automated data source setup. |
| 26 | GPU Health Dashboard | Dashboard JSON via `grafana_api` client: temp, memory, utilization panels. | Live GPU dashboard. |
| 27 | Prometheus Alert Rules | `alerts.yml`: `HighGPUMemory` if `gpu_memory_usage > 95%` for 5 min. | Alert firing on overload. |
| 28 | Alert Receiver Webhook | FastAPI `/webhook` endpoint receives Alertmanager JSON, publishes to `EventBus`. | External alerts become internal events. |
| 29 | Log Pattern Scanner | `log_scanner.py` queries Loki with LogQL for `"CUDA out of memory"`, raises `CudaOomEvent`. | Automatic error detection from logs. |
| 30 | Fault Tree Structure | `fault_tree.json`: Root `GPU_Issue` → `OOM` (metrics+logs) / `Driver_Hang` (logs+stall). | Machine-readable diagnosis tree. |
| 31 | Diagnosis Engine Core | `diagnosis_engine.py` loads fault tree, subscribes to `EventBus`, evaluates rules. | Engine identifies "VRAM Exhaustion" from alert+log combo. |
| 32 | Time-Correlation Logic | On "Container Restart" event, query Loki for logs 60s prior, correlate "OOMKiller". | Groups symptoms into one incident. |
| 33 | Knowledge Base | `knowledge_base.py`, SQLite table: symptom → cause → solution. | Persistent fix database. |
| 34 | Link Diagnosis to Knowledge Base | Diagnosis engine queries KB after root cause found, returns solution string. | Engine outputs cause + fix together. |
| 35 | Repair Action Executor | `repair_actions.py`, `execute_repair(action_type, target)`, case `"restart_container"` calls `DockerClient.restart()`. | Engine can act on infra. |
| 36 | Safe Rollback Logic | Snapshot container image/config before repair, `rollback(target)` reverts to snapshot. | Reversible repairs. |
| 37 | Health Check Scheduler | `scheduler.py` using `schedule` lib, runs `health_check()` every 5 min. | Automated recurring checks. |
| 38 | Auto-Healing Pipeline | Wire scheduler → diagnosis → repair → re-verify health. | Fully automated self-healing loop. |
| 39 | Multi-Client Tenant Isolation | `config_manager` holds `clients` dict; diagnosis/repair/cloud clients take `client_id` and use only that client's SSH keys, K8s context, AWS/GCP/Azure credentials. | Client A and Client B never cross-contaminate, across every provider. |

---

## Phase 3: GPU + Full Cloud Cost Optimization (Days 40–48)

| Day | Task | Details | Deliverable |
|---|---|---|---|
| 40 | GPU Profiling Trigger | In `gpu_manager`, if latency > 100ms for 3 checks, auto-run `nvidia-smi pmon` for a 10s trace. | Automatic performance data capture. |
| 41 | Store Profiling Output | Write to `/profiling/client_x/date_time/` with metadata JSON. | Organized raw performance data. |
| 42 | GPU Cost Optimizer | `cost_optimizer.py` queries Prometheus for 7-day avg GPU utilization, flags instances below 20%. | "Zombie GPU" report. |
| 43 | GPU Right-Sizing Recommendations | Compare current GPU type to cheaper alternatives (A100 → T4/L4). | Cost-saving tickets. |
| 44 | Idle/Oversized Compute Detector | Extend `cost_optimizer.py` using `CloudResource` data: flag EC2/GCE/Azure VMs with low CPU/mem utilization over 7 days. | Non-GPU wasted-compute report. |
| 45 | Unattached Storage Scanner | Check EBS volumes / persistent disks with no attached instance ID. | Orphaned storage report. |
| 46 | Orphaned Load Balancer Detector | Check LBs with near-zero request count in CloudWatch/Cloud Monitoring over 7 days. | Dead-LB report. |
| 47 | Reserved Instance / Savings Plan Recommender | Pull on-demand billing data, calculate what RI/savings-plan pricing would have cost for the same usage. | "Switch to X, save $Y/month" output. |
| 48 | Egress Cost Auditor | Pull billing API data for cross-region/internet data transfer costs, flag anomalies vs. historical baseline. | Flags hidden network cost drains. |

---

## Phase 4: Reporting & New Service Lines (Days 49–53)

| Day | Task | Details | Deliverable |
|---|---|---|---|
| 49 | Unified Cost Report Generator | Merge Days 42–48 findings (GPU, compute, storage, LB, RI, egress) into one report keyed by `CloudResource`. | Single client-facing cost report — main sales document. |
| 50 | Kubernetes Cost & Rightsizing | Compare pod `resource.requests/limits` to actual usage via `kubectl top`/metrics API; flag unused PVCs and empty namespaces. | K8s-specific waste report. |
| 51 | CI/CD Pipeline Audit | Pull build logs/timings from GitHub Actions/GitLab CI API, flag jobs with longest average duration and highest failure rate. | "Slowest pipelines" report for engineering managers. |
| 52 | Plugin Architecture | C++ abstract base class `EnginePlugin` (`initialize()`, `execute()`, `shutdown()`); wrap diagnosis engine as a plugin. | Pluggable system — cost/K8s/CI-CD modules all become plugins. |
| 53 | Migration Advisory Report | Using existing multi-cloud + cost data, generate a comparison: current provider/region cost vs. estimated cost on an alternative. | One-time high-fee advisory deliverable. |

---

## Phase 5: Productize and Ship (Days 54–60)

| Day | Task | Details | Deliverable |
|---|---|---|---|
| 54 | FastAPI Entrypoint + Client CRUD | `main.py`, `POST /clients`, `GET /clients`, `GET /clients/{id}/health`, plus `GET /clients/{id}/cost-report`. | Full API control including cost data. |
| 55 | CLI Tool | `aioctl` via `click`: `aioctl client list`, `aioctl diagnose --client acme`, `aioctl repair --client acme --auto`, `aioctl cost report --client acme`. | One CLI covering ops and cost. |
| 56 | Streamlit Dashboard | Client table with status colors, "Run Diagnostics" button, plus a Cost Report tab and Cloud Inventory tab. | GUI covering diagnostics and cost together. |
| 57 | Reliability Pass | Exponential backoff retries (`retry.py`, 1s/2s/4s/8s) on all SSH/Docker/K8s/cloud SDK calls; global timeouts (10s SSH, 30s Docker, 60s K8s/cloud). | Engine survives network flakiness and hangs. |
| 58 | Security Hygiene Pass | Move SSH keys and cloud credentials to env vars via `secrets_manager.py`; enable TLS on the FastAPI server (`ssl_keyfile`/`ssl_certfile`). | No plaintext secrets in Git, encrypted internal traffic. |
| 59 | Audit Logger + Docs | `@audit_log` decorator logs every repair/rollback/cost-report action per client; write `ONBOARDING.md`, `USER_MANUAL.md`, `OPS_MANUAL.md`. | Tamper-evident action log + full documentation set. |
| 60 | Final Demonstration | Mock environment: inject a GPU OOM (watch auto-heal fix it), run the unified cost report, K8s rightsizing report, and migration advisory against a mock multi-cloud account. Record the whole thing. | **AI Infrastructure & Cloud Ops Engine v1.0** — self-healing infra + full cloud cost optimization + a sellable consulting report, all demonstrated end to end. |

---

## Architecture Summary

- **Core (C++)**: Docker client, K8s client, event processing, plugin base class
- **Modules (Python)**: SSH executor, config manager, GPU manager, cloud clients (AWS/GCP/Azure), diagnosis engine, cost optimizer, knowledge base
- **Interfaces**: REST API (FastAPI), CLI (`aioctl`), Web Dashboard (Streamlit)
- **Observability**: Prometheus, Grafana, Loki
- **Service Lines**: Self-healing infra ops · Full multi-cloud cost optimization · Kubernetes rightsizing · CI/CD audits · Migration advisory
