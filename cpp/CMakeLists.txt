include(CTest)

add_library(voom_common
  common/src/graph.cpp)
target_include_directories(voom_common PUBLIC common/include)

add_library(voom_route_opt
  route_opt/src/dijkstra.cpp)
target_include_directories(voom_route_opt PUBLIC route_opt/include common/include)
target_link_libraries(voom_route_opt PUBLIC voom_common)

add_library(voom_vrp
  vrp/src/vrp_solver.cpp)
target_include_directories(voom_vrp PUBLIC vrp/include common/include route_opt/include)
target_link_libraries(voom_vrp PUBLIC voom_route_opt)

add_library(voom_sim sim/src/sim_engine.cpp)
  target_include_directories(voom_sim PUBLIC sim/include common/include)

add_library(voom_eta eta/src/eta_core.cpp)
  target_include_directories(voom_eta PUBLIC eta/include common/include)

add_library(voom_demand demand/src/balancer.cpp)
target_include_directories(voom_demand PUBLIC demand/include common/include)

add_subdirectory(server)

if(VOOM_ENABLE_TESTS)
  add_subdirectory(tests)
endif()

if(VOOM_ENABLE_BENCH)
  add_subdirectory(bench)
endif()