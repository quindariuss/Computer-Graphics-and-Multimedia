cmake_minimum_required(VERSION 3.17)
project(m08_procedural_textures)


link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)



add_executable(01-stripes 01-stripes/stripes.cpp)
configure_file(01-stripes/fragment_shader01.glsl .)
configure_file(01-stripes/vertex_shader01.glsl .)

add_executable(03-bricks 03-bricks/bricks.cpp)
configure_file(03-bricks/fragment_shader03.glsl .)
configure_file(03-bricks/vertex_shader03.glsl .)


add_executable(05-fractal 05-fractal/fractal.cpp)
configure_file(05-fractal/fragment_shader05.glsl .)
configure_file(05-fractal/vertex_shader05.glsl .)
