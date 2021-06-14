cmake_minimum_required(VERSION 3.17)
project(m01_first_program)


link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)

add_executable(problem-1 problem-1/one_point.cpp)
configure_file(problem-1/fragment_shader01.glsl .)
configure_file(problem-1/vertex_shader01.glsl .)

add_executable(problem-2 problem-2/one_point.cpp)
configure_file(problem-2/fragment_shader02.glsl .)
configure_file(problem-2/vertex_shader02.glsl .)

add_executable(problem-3 problem-3/one_point.cpp)
configure_file(problem-3/fragment_shader03.glsl .)
configure_file(problem-3/vertex_shader03.glsl .)

add_executable(problem-4 problem-4/one_point.cpp)
configure_file(problem-4/fragment_shader04.glsl .)
configure_file(problem-4/vertex_shader04.glsl .)

add_executable(problem-5 problem-5/one_point.cpp)
configure_file(problem-5/fragment_shader05.glsl .)
configure_file(problem-5/vertex_shader05.glsl .)

add_executable(problem-6 problem-6/one_point.cpp)
configure_file(problem-6/fragment_shader06.glsl .)
configure_file(problem-6/vertex_shader06.glsl .)





