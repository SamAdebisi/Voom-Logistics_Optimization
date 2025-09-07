Voom is a logistics optimization stack. C++23 core for routing, VRP, simulation, ETA windows, and demand balancing. Python/Scala/Go for ML and services. Docker and Kubernetes for scale. Prometheus/Grafana for observability.

## Components
- **C++ core**: Dijkstra, A*, metaheuristics stubs, VRP solver, sim engine, ETA core, demand balancer.
- **Optimizer gRPC** (C++): single entry for core algorithms.
- **ML ETA** (Python/FastAPI): gradient-boosting or DL correction layer.
- **Gateway** (Go): simple HTTP, Prometheus metrics, calls Optimizer via gRPC.
- **Assignment Service** (Scala/Akka HTTP): historical replay and assignment strategies.
- **Benchmarking** (C++ Google Benchmark + Python plots).

## Quickstart
```bash
# C++ core
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build

# Run services locally
docker compose -f deploy/compose/docker-compose.yml up --build

# Kubernetes (kustomize)
kubectl apply -k deploy/k8s/base
````

## Repo tasks

```bash
make build        # cmake build
make test         # c++ gtest + python + go + scala
make docker       # build all images
make bench        # run google benchmark
make lint         # clang-tidy + format checks
```
