find_package(benchmark REQUIRED)
add_executable(bench_astar bench_astar.cpp)
target_link_libraries(bench_astar PRIVATE benchmark::benchmark voom_route_opt)