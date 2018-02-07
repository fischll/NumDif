
# we will need glut and opengl to compile the pendulum code
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(pendulum_DAE pendulum_DAE.cpp rattle.cpp)

# add the directories for the glut headers to the include path (the variables LIB_INCLUDE_DIRS
# are set by find_package(LIB)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# link the glut libraries to our executable (again the variables are set by find_package)
target_link_libraries(pendulum_DAE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# link to our blas (because we need the CalcInverse from there)
target_link_libraries(pendulum_DAE mybla)
