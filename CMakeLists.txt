cmake_minimum_required(VERSION 3.0.0)
project(ysh8361 VERSION 0.1.0)

include(CTest)
enable_testing()

link_libraries(jemalloc pthread)
add_executable(single-jemalloc single-jemalloc.cpp)
add_executable(single-malloc single-malloc.cpp)
add_executable(multi-jemalloc multi-jemalloc.cpp)
add_executable(multi-malloc multi-malloc.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
