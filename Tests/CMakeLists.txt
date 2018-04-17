
cmake_minimum_required(VERSION 3.1)
project(tests)
# The bla library will need the C++11 standard
set(CMAKE_CXX_STANDARD 11)

# set the install folder
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

# create our first 2 executables:

add_executable(DifUe DifUe.cpp)

target_link_libraries(DifUe mybla)


# install them to the install folder (relative to CMAKE_INSTALL_PREFIX)
install(TARGETS DifUe DESTINATION .)

add_directory
# add other folders such that they are built as well
#add_subdirectory(ode/bla)
#add_subdirectory(../rattle)