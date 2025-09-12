FROM debian:stable AS build
RUN apt-get update && apt-get install -y build-essential cmake ninja-build git pkg-config libprotobuf-dev protobuf-compiler grpc-proto grpc-dev libgrpc++-dev
WORKDIR /src
COPY . .
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j

FROM debian:stable-slim
COPY --from=build /src/build/cpp/server/optimizer_service /usr/local/bin/optimizer_service
EXPOSE 50051
ENTRYPOINT ["/usr/local/bin/optimizer_service","0.0.0.0:50051"]