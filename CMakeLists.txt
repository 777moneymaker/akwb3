cmake_minimum_required(VERSION 3.15)
project(akwb3)

set(CMAKE_CXX_STANDARD 14)

add_executable(akwb3 main.cpp Libs/Map.cpp Libs/Map.hpp)