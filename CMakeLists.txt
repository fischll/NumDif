
# The bla library will need the C++11 standard
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# create our first 2 executables:
add_executable(demo_bla demo_bla.cpp)
add_executable(ode_demo ode_demo.cpp)

# add other folders such that they are built as well
add_subdirectory(bla)
add_subdirectory(rattle)
