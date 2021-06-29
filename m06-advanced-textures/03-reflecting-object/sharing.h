#pragma once


#include <GLM/gtc/type_ptr.hpp>


#include <glad/gl.h>

#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/load_shaders.h"


void skybox_display();

void skybox_setup(cs4722::view *a_view); //, GLuint cube_texture_unit);

//void objects_setup(cs4722::view* view);
//void objects_display();

void parts_setup(cs4722::view* view);
void parts_display();

void reflecting_display();
void reflecting_setup(cs4722::view* view, GLuint cube_texture_unit);

