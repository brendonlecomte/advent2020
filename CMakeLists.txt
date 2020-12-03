cmake_minimum_required(VERSION 3.16)

# set the project name
project(advent)


# add the executable
add_executable(advent main.cpp)

set_property(TARGET advent PROPERTY CXX_STANDARD 17)
