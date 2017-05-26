cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)

FILE(GLOB cpp_sources "*.cpp" "impl/*.cpp")
add_library (commander ${cpp_sources} linenoise.c)
