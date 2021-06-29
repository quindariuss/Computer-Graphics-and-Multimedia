cmake_minimum_required(VERSION 3.17)
project(m03-transformation)


link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)

# add_compile_definitions(_GLFW_WIN32)


configure_file(fragment_shader-m04.glsl .)
configure_file(vertex_shader-m04.glsl .)

add_executable(01-static-transform 01-static-transform/static-transform.cpp 05B-oscillation/part_oscillating.cpp 05B-oscillation/part_oscillating.h)
add_executable(01A-use-transform 01A-use-transform/static-transform-use-transform.cpp)
add_executable(02-use-part-and-attributes 02-use-part-and-attributes/use_part.cpp)
add_executable(03-multiple-parts 03-multiple-parts/multiple_parts.cpp)
add_executable(04-shared-shapes 04-shared-shapes/shared_shapes.cpp)
add_executable(04A-buffer-utilities 04A-buffer-utilities/shared_shapes_buffer_utilities.cpp)
add_executable(05-animation 05-animation/animation.cpp)
add_executable(05A-rotate-about-center 05A-rotate-about-center/rotate-about-center.cpp)
add_executable(05B-oscillation 05B-oscillation/oscillation.cpp 05B-oscillation/part_oscillating.cpp)
add_executable(06-animation-many 06-animation-many/animation_many.cpp)

add_executable(07-use-material 07-use-material/use_material.cpp)
configure_file(07-use-material/fragment_shader-07.glsl .)
configure_file(07-use-material/vertex_shader-07.glsl .)

add_executable(08-mix-material-shape-pattern 08-mix-material-shape-pattern/mix_material_shape.cpp)
configure_file(08-mix-material-shape-pattern/fragment_shader-08.glsl .)
configure_file(08-mix-material-shape-pattern/vertex_shader-08.glsl .)
