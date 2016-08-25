cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(Baseball_Field_CG)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(Baseball_Field_CG src/BaseballField.cpp headers/StraightLineAndCircle.h headers/Bresenham.h headers/myComboBox.h)

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Baseball_Field_CG ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Baseball_Field_CG Qt5::Widgets)
TARGET_LINK_LIBRARIES(Baseball_Field_CG ${FLTK_LIBRARIES})