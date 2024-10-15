cmake_minimum_required(VERSION 3.25) 
project(SeaBattle)                      
set(CMAKE_CXX_STANDARD 17)

add_executable(seabattle)
include_directories(seabattle src)
add_subdirectory(src)