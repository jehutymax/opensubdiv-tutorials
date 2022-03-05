cmake_minimum_required(VERSION 3.21)
project(subd_tutorials)

set(CMAKE_CXX_STANDARD 20)

# OSD_INCLUDE_DIR
# OSD_LIB_DIR

if (NOT DEFINED OSD_INCLUDE_DIR)
    set(OSD_INCLUDE_DIR "/media/Projects/github/OpenSubdiv/install/include" CACHE PATH "OpenSubdiv include directory.")
endif ()

if (NOT DEFINED OSD_LIB_DIR)
    set(OSD_INCLUDE_DIR "/media/Projects/github/OpenSubdiv/install/include" CACHE PATH "OpenSubdiv library directory.")
endif ()

add_executable(far-one far-one.cpp)
add_executable(far-two far-two.cpp)
target_include_directories(far-one PUBLIC ${OSD_INCLUDE_DIR})
target_link_directories(far-one PUBLIC ${OSD_LIB_DIR})
target_link_libraries(far-one osdCPU osdGPU)
target_include_directories(far-two PUBLIC ${OSD_INCLUDE_DIR})
target_link_directories(far-two PUBLIC ${OSD_LIB_DIR})
target_link_libraries(far-two osdCPU osdGPU)