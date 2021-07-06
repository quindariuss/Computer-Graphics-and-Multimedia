


#include "GLM/gtc/type_ptr.hpp"



#include <glad/gl.h>


#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/load_shaders.h"


static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::part*> part_list;

static GLuint transform_loc;
static GLuint sampler_loc;


void init()
{

    the_view = new cs4722::view();
//    the_view->enable_logging = true;
    the_view->set_flup(glm::vec3(0.202971,-0.227978,-0.952277),
                       glm::vec3(-0.978031,0,-0.20846),
                       glm::vec3(0.0475242,0.973667,-0.222969),
                       glm::vec3(-0.146291,0.195185,1.3214));
    



    program = cs4722::load_shaders("vertex_shader3.glsl","fragment_shader3.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");
    sampler_loc = glGetUniformLocation(program, "sampler");

    glEnable(GL_DEPTH_TEST);


    /*
     *  Create two textures, one from a file and one procedurally generated
        Note the different texture units assigned.
     */
    cs4722::init_texture_from_file("../media/tulips-bed-2048x2048.png", 2);
    cs4722::init_texture_computed(1, 128);


    cs4722::shape* b = new cs4722::sphere(15, 50);
    auto* part = new cs4722::part_rotating();
    part->the_shape = (b);
    part->world_transform.translate = (glm::vec3(.5, -.5, 0));
    part->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    part->rotation_rate = (M_PI / 3);
    part->world_transform.scale = (glm::vec3(.4f, .6f, .4f));
    part->animation_transform.rotation_center =
            part->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    /*
     * Each part can be assigned a texture unit, this is used in the display function
     */
    part->texture_unit = 1;
    part_list.push_back(part);


    cs4722::shape* b1 = new cs4722::block();
    auto* part1 = new cs4722::part_rotating();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(-.5, 0, 0));
    part1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1->rotation_rate = (M_PI / 3);
    part1->world_transform.scale = (glm::vec3(.2f, .6f, .2f));
    part1->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part1->texture_unit = 2;

    part_list.push_back(part1);


    cs4722::init_buffers(program, part_list, "bPosition", "", "bTextureCoord");

}


//----------------------------------------------------------------------------
//
// display
//


void
display()
{

    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect, the_view->perspective_near);
    auto vp_transform = projection_transform * view_transform;


    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;


    for (auto part : part_list) {

        part->animate(time, delta_time);

        auto model_transform = part->animation_transform.matrix() * part->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        /*
         * Set the texture unit to use for this part
         */
        glUniform1i(sampler_loc, part->texture_unit);

        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
    }
}


int
main(int argc, char** argv)
{
    glfwInit();

    auto aspect_ratio = 16.0/9.0;
    auto* window = cs4722::setup_window("Multiple Textures", 0.9,
                                        aspect_ratio);

    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();

    init();
    the_view->perspective_aspect = aspect_ratio;

    cs4722::setup_user_callbacks(window);
    glfwSetWindowUserPointer(window, the_view);
	
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
