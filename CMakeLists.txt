cmake_minimum_required(VERSION 3.0.0)
project(vcom VERSION 0.1.0)

file(GLOB_RECURSE sources "src/*.*")
include_directories("include")

add_executable(vcom ${sources})
