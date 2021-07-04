cmake_minimum_required(VERSION 3.17)
project(assignment04)

link_libraries(cs4722 cs4722external glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)



add_executable(01-elliptical-orbit
        01-elliptical-orbit/elliptical_orbit.cpp
        #part_elliptical_orbit.cpp
        )
configure_file(01-elliptical-orbit/01-fragment_shader.glsl .)
configure_file(01-elliptical-orbit/01-vertex_shader.glsl .)

add_executable(02-alternate-specifications
        02-alternate-specifications/alternate_specifications.cpp
        # part_elliptical_orbit.cpp
        )
configure_file(02-alternate-specifications/02-fragment_shader.glsl .)
configure_file(02-alternate-specifications/02-vertex_shader.glsl .)

