#!/usr/bin/env bash
set -euo pipefail
ctest --test-dir build || true
./build/cpp/bench/bench_astar || true