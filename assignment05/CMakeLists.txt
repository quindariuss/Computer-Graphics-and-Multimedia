cmake_minimum_required(VERSION 3.17)
project(m06_advanced_textures)



link_libraries(cs4722 cs4722external glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)


#configure_file(02-sky-box/parts_vertex_shader07.glsl .)
#configure_file(02-sky-box/parts_fragment_shader07.glsl .)

add_executable(assignment05 assignment05/skybox.cpp
        assignment05/setup_skybox.cpp
        assignment05/setup_parts.cpp)
configure_file(assignment05/skybox_fragment_shader02.glsl .)
configure_file(assignment05/parts_vertex_shader02.glsl .)
configure_file(assignment05/skybox_vertex_shader02.glsl .)
configure_file(assignment05/parts_fragment_shader02.glsl .)



