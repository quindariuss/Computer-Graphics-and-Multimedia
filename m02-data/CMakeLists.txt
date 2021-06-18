cmake_minimum_required(VERSION 3.17)
project(m02_data)
set(CMAKE_CXX_STANDARD 20)


link_libraries(cs4722 cs4722external glfw3 opengl32 glu32)

include_directories( Common ../Common)
link_directories( Common ../Common)

add_executable(02-many-points 02-many-points/many_points.cpp)
configure_file(02-many-points/fragment_shader02.glsl .)
configure_file(02-many-points/vertex_shader02.glsl .)


add_executable(03-many-colors 03-many-colors/many_colors.cpp)
configure_file(03-many-colors/vertex_shader03.glsl .)
configure_file(03-many-colors/fragment_shader03.glsl .)

add_executable(04-square 04-square/example4-square.cpp)
configure_file(04-square/vertex_shader04.glsl .)
configure_file(04-square/fragment_shader04.glsl .)

add_executable(05-shapes 05-shapes/shapes.cpp)
configure_file(05-shapes/vertex_shader05.glsl .)
configure_file(05-shapes/fragment_shader05.glsl .)

add_executable(06-coordinate-orientation 06-coordinate-orientation/coordinate_orientation.cpp)
configure_file(06-coordinate-orientation/vertex_shader06.glsl .)
configure_file(06-coordinate-orientation/fragment_shader06.glsl .)

