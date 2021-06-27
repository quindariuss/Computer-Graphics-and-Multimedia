cmake_minimum_required(VERSION 3.17)
project(assignment03)

link_libraries(cs4722 cs4722external glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)

add_executable(assignment03 assignment03/assignment03.cpp)
configure_file(assignment03/fragment_shader.glsl .)
configure_file(assignment03/vertex_shader.glsl .)
