
cmake_minimum_required(VERSION 3.1)
project(ode)
# The bla library will need the C++11 standard
set(CMAKE_CXX_STANDARD 11)

# set the install folder
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

# create our first 2 executables:
#add_executable(demo_bla demo_bla.cpp)
#add_executable(ode_demo ode_demo.cpp)
#add_executable(pendulum pendulum.cpp)
#add_executable(circuit circuit.cpp)
#add_executable(testImplRK test_impl_RK.cpp)
#add_executable(testNewton test_Newton.cpp)
#add_executable(diode diode.cpp)
#add_executable(circuit_14 Bsp14_circuit.cpp)
#add_executable(test_12 test_12.cpp)
add_executable(chr chemicalreactions.cpp)

#target_link_libraries(pendulum mybla)
#target_link_libraries(circuit mybla)
#target_link_libraries(testImplRK mybla)
#target_link_libraries(testNewton mybla)
#target_link_libraries(diode mybla)
#target_link_libraries(circuit_14 mybla)
#target_link_libraries(test_12 mybla)
target_link_libraries(chr mybla)


# install them to the install folder (relative to CMAKE_INSTALL_PREFIX)
install(TARGETS chr DESTINATION .)

# add other folders such that they are built as well
add_subdirectory(bla)
add_subdirectory(rattle)
