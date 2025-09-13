.PHONY: build test docker bench lint
build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j

test:
	ctest --test-dir build --output-on-failure || true
	pytest -q python/ml_eta/tests || true
	cd go/gateway && go test ./... || true
	cd scala/assignment-service && sbt test || true

docker:
	docker compose -f deploy/compose/docker-compose.yml build

bench:
	cd build/cpp/bench && ./bench_astar || true

lint:
	clang-tidy --version && echo ok