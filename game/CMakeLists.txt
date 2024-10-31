cmake_minimum_required(VERSION 3.25) 
project(SeaBattle)                      
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)


add_executable(seabattle)
include_directories(src) 
add_subdirectory(src)
