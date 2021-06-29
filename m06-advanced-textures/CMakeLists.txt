cmake_minimum_required(VERSION 3.17)
project(m06_advanced_textures)



link_libraries(cs4722 cs4722external glfw3dll opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories( Common ../Common)
link_directories( Common ../Common)

add_executable(01-cube-map 01-cube-map/cube-map.cpp)
configure_file(01-cube-map/vertex_shader01.glsl .)
configure_file(01-cube-map/fragment_shader01.glsl .)

#configure_file(02-sky-box/parts_vertex_shader07.glsl .)
#configure_file(02-sky-box/parts_fragment_shader07.glsl .)

add_executable(02-sky-box 02-sky-box/skybox.cpp
        02-sky-box/setup_skybox.cpp
        02-sky-box/setup_parts.cpp)
configure_file(02-sky-box/skybox_vertex_shader02.glsl .)
configure_file(02-sky-box/skybox_fragment_shader02.glsl .)
configure_file(02-sky-box/parts_vertex_shader02.glsl .)
configure_file(02-sky-box/parts_fragment_shader02.glsl .)

#add_executable(03-reflecting-object 03-reflecting-object/setup_parts.cpp 03-reflecting-object/setup_skybox.cpp
#        03-reflecting-object/skybox.cpp 03-reflecting-object/setup_reflecting.cpp)
add_executable(03-reflecting-object 02-sky-box/setup_parts.cpp 02-sky-box/setup_skybox.cpp
        03-reflecting-object/reflecting.cpp 03-reflecting-object/setup_reflecting.cpp)
configure_file(03-reflecting-object/reflecting_vertex_shader03.glsl .)
configure_file(03-reflecting-object/reflecting_fragment_shader03.glsl .)

add_executable(04-render-to-texture 04-render-to-texture/render-to-texture.cpp 04-render-to-texture/setup_parts.cpp
        04-render-to-texture/setup_view_in_view.cpp)
configure_file(04-render-to-texture/view_in_view_vertex_shader04.glsl .)
configure_file(04-render-to-texture/view_in_view_fragment_shader04.glsl .)
#configure_file(04-render-to-texture/parts_vertex_shader09.glsl .)
#configure_file(04-render-to-texture/parts_fragment_shader09.glsl .)

add_executable(05-image-processing 05-image-processing/image-processing.cpp
        05-image-processing/setup_parts.cpp 05-image-processing/setup_view_in_view.cpp)
configure_file(05-image-processing/image_processing_vertex_shader.glsl .)
configure_file(05-image-processing/image_processing_fragment_shader.glsl .)


add_executable(06-point-sprites 06-point-sprites/point_sprites.cpp)
configure_file(06-point-sprites/vertex_shader06.glsl .)
configure_file(06-point-sprites/fragment_shader06.glsl .)

add_executable(07-point-sprites-2 07-point-sprites-2/point_sprites.cpp)
configure_file(07-point-sprites-2/vertex_shader12.glsl .)
configure_file(07-point-sprites-2/fragment_shader12.glsl .)


