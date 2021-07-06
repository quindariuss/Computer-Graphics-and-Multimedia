


#include <GLM/vec4.hpp>
#include <GLM/vec2.hpp>
#include <GLM/gtc/type_ptr.hpp>


#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include "cs4722/view.h"
#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/callbacks.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"

static cs4722::view *the_view;
static std::vector<cs4722::part*> part_list;
static GLuint program;
static std::vector<GLuint> texture_list;

static GLuint uTransform;
static GLuint uSampler;


void init()
{
    the_view = new cs4722::view();
    the_view->set_camera_position(glm::vec3(1.5, 1.6, 1.7));


    program = cs4722::load_shaders("vertex_shader3.glsl","fragment_shader3.glsl");
    glUseProgram(program);

    uTransform = glGetUniformLocation(program, "transform");
    uSampler = glGetUniformLocation(program, "sampler");


    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


    auto r_height = 10.0;
    auto r_width = 3.0;
    auto *a_shape = new cs4722::rectangle;
    a_shape->texture_height_scale = (r_height);
    a_shape->texture_width_scale = (r_width);
    auto *a_part = new cs4722::part();
    a_part->the_shape = (a_shape);
    a_part->world_transform.rotation_axis = (glm::vec3(1, 0, 0));
    a_part->world_transform.rotation_angle = (-M_PI / 2);
    a_part->world_transform.scale = (glm::vec3(r_width, r_height, 1));
    a_part->texture_unit = 1;

    part_list.push_back(a_part);

    cs4722::init_buffers(program, part_list, "bPosition", "", "bTextureCoord");
}

void init_texture_computed() {

    auto texture_width = 2048;
    auto texture_height = texture_width;
    auto size = texture_width / 8;
	
    auto texture_data = new std::vector<GLubyte>();
    // create data
    for (int r = 0; r < texture_height; r++) {
        for (int c = 0; c < texture_width; c++) {
            auto i = r / size;
            auto j = c / size;
        	if((i+j) % 2 == 0)
        	{
                texture_data->push_back(0);
                texture_data->push_back(0);
                texture_data->push_back(0);
        	} else
        	{
                texture_data->push_back(255);
                texture_data->push_back(255);
                texture_data->push_back(255);

        	}
            texture_data->push_back(255);
        }
    }


    // initialize texture and sampler

    glActiveTexture(GL_TEXTURE1);
    GLuint texture;
    glGenTextures(1, &texture);
    texture_list.push_back(texture);
    glBindTexture(GL_TEXTURE_2D, texture);

//    std::cout << "texture in create texture: " << texture << std::endl;

    auto number_of_levels = 10;
    auto internal_format = GL_RGBA8;
    auto external_format = GL_RGBA;

   
    glTexStorage2D(GL_TEXTURE_2D, number_of_levels, internal_format, texture_width, texture_height);
//    glBindTexUnit(1, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture_width, texture_height,
       external_format, GL_UNSIGNED_BYTE, texture_data->data());

    // glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, cs4722::x11::aquamarine.as_float());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    auto mag_filter = GL_NEAREST;
    // auto mag_filter = GL_LINEAR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    // auto wrap_type = GL_CLAMP_TO_EDGE;
    //auto wrap_type = GL_MIRRORED_REPEAT;
    auto wrap_type = GL_REPEAT;
    //auto wrap_type = GL_CLAMP_TO_BORDER;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_type);
    glGenerateMipmap(GL_TEXTURE_2D);
}


void init_texture_computed_from_text() {

    glActiveTexture(GL_TEXTURE0);
    GLuint tex;
    glGenTextures(1, &tex);
    std::cout << "texture in create texture 2: " << tex << std::endl;
    texture_list.push_back(tex);

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexStorage2D(GL_TEXTURE_2D, 7, GL_RGBA8, 64, 64);

    unsigned int* data = new unsigned int[64 * 64];

    unsigned int colors[] = { 0xFF0000FF, 0xFF00FF00, 0xFFFF0000, 0xFF00FFFF, 0xFFFF00FF, 0xFFFFFF00, 0xFFFFFFFF };

    int i, j, k;
    int n;

    for (i = 0; i < 7; i++)
    {
        n = 0;
        for (j = 0; j < (64 >> i); j++)
        {
            for (k = 0; k < (64 >> i); k++)
            {
                data[n] = (k ^ (64 - j)) * 0x04040404;
                n++;
            }
        }
        glTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, 64 >> i, 64 >> i, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 4.5f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    delete[] data;
}


void
display()
{


    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect, the_view->perspective_near);
    auto vp_transform = projection_transform * view_transform;



    for (auto obj : part_list) {
        auto model_transform =  obj->animation_transform.matrix() *  obj->world_transform.matrix();
        auto transform = vp_transform * model_transform;
    	glUniformMatrix4fv(uTransform, 1, GL_FALSE, glm::value_ptr(transform));
        glUniform1i(uSampler, obj->texture_unit);
        glDrawArrays(GL_TRIANGLES, obj->the_shape->buffer_start,
            obj->the_shape->buffer_size);
    }
}




//int old_width, old_height, old_xpos, old_ypos;

void general_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//    auto* the_scene = static_cast<cs4722::scene*>(glfwGetWindowUserPointer(window));
    auto texture_unit = part_list[0]->texture_unit;
    auto texture = texture_list[texture_unit];
	


	if(action != GLFW_PRESS && action != GLFW_REPEAT)
	{
		
	}
    else if (key == GLFW_KEY_DOWN)
    {
        auto* obj = part_list[0];
        obj->world_transform.rotation_angle -=  M_PI / 30;

    }
    else if (key == GLFW_KEY_UP)
    {
        auto* obj = part_list[0];
        obj->world_transform.rotation_angle += M_PI / 30;

    }
    else if (key == GLFW_KEY_0)
    {
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    else if(key == GLFW_KEY_1)
    {
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else if (key == GLFW_KEY_5)
    {
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else if (key == GLFW_KEY_4)
    {
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }
    else if (key == GLFW_KEY_3)
    {
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    }
    else if (key == GLFW_KEY_2)
    {
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    }
    else if(key == GLFW_KEY_T)
    {
        part_list[0]->texture_unit = 1 - part_list[0]->texture_unit;
    }
    else
    {
        cs4722::general_key_callback(window, key, scancode, action, mods);
    }

}


int
main(int argc, char** argv)
{

    /*
    up arrow        Raise part
	down arrow      Lower part
	0               nearest
	1               linear
	5               linear linear
	4               linear nearest
	3               nearest linear
	2               nearest nearest
    T               toggle texture
    
     */

	
    std::cout << "Keys to activate example features:" << std::endl;
    std::cout << "up arrow        Raise surface" << std::endl;
    std::cout << "down arrow      Lower surface" << std::endl;
    std::cout << "0               nearest" << std::endl;
    std::cout << "1               linear" << std::endl;
    std::cout << "2               nearest nearest" << std::endl;
    std::cout << "3               nearest linear" << std::endl;
    std::cout << "4               linear nearest" << std::endl;
    std::cout << "5               linear linear" << std::endl;
    std::cout << "T               Toggle texture" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    glfwInit();
    auto aspect_ratio = 16.0/9.0;
    auto *window = cs4722::setup_window("Min Filters", .9, aspect_ratio);
    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();
    init();
    the_view->perspective_aspect = aspect_ratio;

    init_texture_computed_from_text();
    init_texture_computed();

    glfwSetWindowUserPointer(window, the_view);

    glfwSetKeyCallback(window, general_key_callback);
     glfwSetCursorPosCallback(window, cs4722::move_callback);
    glfwSetWindowSizeCallback(window, cs4722::window_size_callback);

	
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);

        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
