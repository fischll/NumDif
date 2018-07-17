
cmake_minimum_required(VERSION 3.1)
project(ode)
# The bla library will need the C++11 standard
set(CMAKE_CXX_STANDARD 11)

# set the install folder
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})#/install)

add_executable(04 04_pendulum.cpp)
add_executable(05 05_pendulum.cpp)
add_executable(08 08_circuit.cpp)
add_executable(12 12_gauß.cpp)
add_executable(13 13_diode.cpp)
add_executable(14 14_circuit.cpp)
add_executable(18 18_chemie.cpp)
add_executable(22 22_satelit.cpp)
add_executable(26 26_pen_h_allg.cpp)
add_executable(26s 26_pen_h_sep.cpp)
add_executable(32 32_pen_dae.cpp)
add_executable(41 41_heateqn.cpp)
add_executable(43 43_monom.cpp)

target_link_libraries(04 mybla)
target_link_libraries(05 mybla)
target_link_libraries(08 mybla)
target_link_libraries(12 mybla)
target_link_libraries(13 mybla)
target_link_libraries(14 mybla)
target_link_libraries(18 mybla)
target_link_libraries(22 mybla)
target_link_libraries(26s mybla)
target_link_libraries(32 mybla)
target_link_libraries(41 mybla)
target_link_libraries(43 mybla)
# install them to the install folder (relative to CMAKE_INSTALL_PREFIX)
install(TARGETS 04 05 08  12 13 14 18 22 26 26s 32 41 43 DESTINATION .)

# add other folders such that they are built as well
add_subdirectory(bla)
add_subdirectory(rattle)

