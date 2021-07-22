#pragma once

 /*
  * Headers of functions that will be used in function 'main' to setup and render the
  * different parts of the scene.
  */

 #include <GLM/gtc/type_ptr.hpp>



#include <glad/gl.h>


#include "cs4722/view.h"
#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/load_shaders.h"


void skybox_display();

void skybox_setup(cs4722::view *a_view);

void parts_setup(cs4722::view* view);


void parts_display();
