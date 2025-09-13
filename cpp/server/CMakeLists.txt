find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

+set(PROTO_SRC "${PROJECT_SOURCE_DIR}/proto/optimizer.proto")
 protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC})
 grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC})

add_library(optimizer_proto ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS})
target_include_directories(optimizer_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_executable(optimizer_service optimizer_service.cc optimizer_service_main.cc)
target_link_libraries(optimizer_service PRIVATE optimizer_proto gRPC::grpc++ voom_route_opt voom_vrp voom_sim voom_eta voom_demand)
