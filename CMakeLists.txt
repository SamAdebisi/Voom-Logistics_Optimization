cmake_minimum_required(VERSION 3.22)
project(voom LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
option(VOOM_ENABLE_TESTS "Enable tests" ON)
option(VOOM_ENABLE_BENCH "Enable benchmarks" ON)

add_subdirectory(cpp)