cmake_minimum_required(VERSION 3.17)
project(m01_first_program)


link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)


add_executable(01-one-point 01-one-point/one_point.cpp)
configure_file(01-one-point/vertex_shader01.glsl .)
configure_file(01-one-point/fragment_shader01.glsl .)