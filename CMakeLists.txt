cmake_minimum_required(VERSION 3.20)
project(parsers)

add_executable(parser main.cpp)
add_subdirectory(src)
target_include_directories(parser PRIVATE inc)

target_compile_features(parser PRIVATE cxx_std_20)
target_compile_options(parser PRIVATE -Wall -Wextra -Werror -fsanitize=address)
target_link_options(parser PRIVATE -fsanitize=address)
