cmake_minimum_required(VERSION 3.17)
project(m07_lighting_and_shading)





link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)

file(GLOB glsls */*.glsl)
foreach(shader ${glsls})
    configure_file(${shader} .)
endforeach()

add_executable(01-no-lighting 01-no-lighting/no-lighting.cpp)
add_executable(02-ambient-light 02-ambient-light/ambient-light.cpp)
add_executable(03-visualize-normals 03-visualize-normals/visualize_normals.cpp)
add_executable(04-adjust-normals 04-adjust-normals/adjust_normals.cpp)
add_executable(05-directional-lighting 05-directional-lighting/directional_lighting.cpp)
add_executable(06-point-lighting 06-point-lighting/point_lighting.cpp)
add_executable(07-shading-textures 07-shading-textures/shading_textures.cpp)


