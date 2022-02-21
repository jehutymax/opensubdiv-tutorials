cmake_minimum_required(VERSION 3.21)
project(subd_tutorials)

set(CMAKE_CXX_STANDARD 20)

add_executable(far-one far-one.cpp)
target_include_directories(far-one PUBLIC /media/Projects/github/OpenSubdiv/install/include)
target_link_directories(far-one PUBLIC /media/Projects/github/OpenSubdiv/install/lib)
target_link_libraries(far-one osdCPU osdGPU)
