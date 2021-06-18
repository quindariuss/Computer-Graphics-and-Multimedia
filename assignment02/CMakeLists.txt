cmake_minimum_required(VERSION 3.17)
project(m02_data)
set(CMAKE_CXX_STANDARD 20)


link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

include_directories( Common ../Common)
link_directories( Common ../Common)

add_executable(01-gradient 01-gradient/gradient.cpp)
configure_file(01-gradient/fragment_shader_gradient.glsl .)
configure_file(01-gradient/vertex_shader_gradient.glsl .)

add_executable(02-solid 02-solid/solid.cpp)
configure_file(02-solid/fragment_shader_solid.glsl .)
configure_file(02-solid/vertex_shader_solid.glsl .)
