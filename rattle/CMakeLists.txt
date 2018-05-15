
# we will need glut and opengl to compile the pendulum code
find_package(OpenGL REQUIRED)
if(NOT WIN32)
find_package(GLUT REQUIRED)
endif(NOT WIN32)

add_executable(pendulum_DAE pendulum_DAE.cpp rattle.cpp)
add_executable(dualpen dualpendulum_DAE.cpp rattle.cpp)

# add the directories for the glut headers to the include path (the variables LIB_INCLUDE_DIRS
# are set by find_package(LIB)
if(WIN32)
  target_include_directories(pendulum_DAE PUBLIC ../windows_GL/include)
  #
else(WIN32)
  target_include_directories(pendulum_DAE PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${GLUT_INCLUDE_DIR}/GL)
  target_include_directories(dualpen PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${GLUT_INCLUDE_DIR}/GL)
endif(WIN32)

# link the glut libraries to our executable (again the variables are set by find_package)
if(WIN32)
target_link_libraries(pendulum_DAE ${CMAKE_CURRENT_SOURCE_DIR}/../windows_GL/lib/freeglut.lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../windows_GL/bin/freeglut.dll DESTINATION .)
#
#
else(WIN32)
  target_link_libraries(pendulum_DAE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
  target_link_libraries(dualpen ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif(WIN32)

# link to our blas
target_link_libraries(pendulum_DAE mybla)
target_link_libraries(dualpen mybla)

install(TARGETS pendulum_DAE dualpen DESTINATION .)
