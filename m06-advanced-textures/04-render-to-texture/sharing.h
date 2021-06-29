#pragma once


#include <GLM/gtc/type_ptr.hpp>
#include <vector>

#include <glad/gl.h>


#include "cs4722/view.h"
#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/load_shaders.h"


const auto fb_texture_unit = 61;
const auto frame_buffer_width = 2048;
const auto frame_buffer_height = frame_buffer_width;


const auto rectangle_width = 20.0;
const auto rectangle_height = 8.0;



void parts_setup(cs4722::view* view);


void parts_display();

void parts_setup_for_fb();

void parts_setup_for_window(GLFWwindow* window);



void view_in_view_setup(cs4722::view *the_view);

void view_in_view_display();


