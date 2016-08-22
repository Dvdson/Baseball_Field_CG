cmake_minimum_required(VERSION 2.8)

project(Baseball_Field_CG)
add_executable(Baseball_Field_CG src/BaseballField.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Baseball_Field_CG ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )