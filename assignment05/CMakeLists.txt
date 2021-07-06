cmake_minimum_required(VERSION 3.17)
project(assignment05)



link_libraries(cs4722 cs4722external glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)

add_executable(assignment05 assignment05/assignment05.cpp)
configure_file(assignment05/fragment_shader.glsl .)
configure_file(assignment05/vertex_shader.glsl .)