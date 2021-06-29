cmake_minimum_required(VERSION 3.17)
project(m04_view_projection)

link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)

configure_file(fragment_shader.glsl .)
configure_file(vertex_shader.glsl .)


add_executable(01-camera 01-camera/animation-with-camera.cpp)
add_executable(02-projection 02-projection/view-and-projection.cpp)
add_executable(03-user-interaction 03-user-interaction/user-interaction.cpp)
add_executable(04-window-events 04-window-events/window_events.cpp)
add_executable(04A-window-events-callbacks-util 04A-window-events-callbacks-util/window_events.cpp)



