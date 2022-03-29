cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(rail VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(include)

add_library(train include/train.hpp
    src/train.cpp
)
add_library(deposit include/deposit.hpp
    src/deposit.cpp
)
add_library(station include/station.hpp
    src/station.cpp
)
add_library(line include/line.hpp
    src/line.cpp
    src/line_input.cpp
    src/line_stations.cpp
    src/line_trains.cpp
)

add_executable(rail rail.cpp src/train.cpp src/deposit.cpp src/station.cpp src/line.cpp src/line_input.cpp src/line_stations.cpp src/line_trains.cpp)

target_link_libraries(rail train deposit station line)