


#include "GLM/gtc/type_ptr.hpp"

#include <glad/gl.h>

#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/texture_utilities.h"  // include texture utilities
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

    the_view->set_flup(glm::vec3(-0.256451,-0.0699429,-0.964024),
                       glm::vec3(-0.96639,0,0.257081),
                       glm::vec3(-0.0179809,0.997551,-0.0675921),
                       glm::vec3(-0.161935,0.111801,0.930503));



    program = cs4722::load_shaders("vertex_shader3.glsl","fragment_shader3.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");
    sampler_loc = glGetUniformLocation(program, "sampler");

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    /*
     * Back to creating a shape and using the buffer utilities.
     */

    cs4722::shape* b1 = new cs4722::sphere(15,30);
    auto* obj1 = new cs4722::part_rotating();
    obj1->the_shape = (b1);
    obj1->world_transform.translate = (glm::vec3(-.5, 0, 0));
    obj1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    obj1->rotation_rate = (M_PI / 3);
    obj1->world_transform.scale = (glm::vec3(.6f, .6f, .6f));
    obj1->animation_transform.rotation_center =
            obj1->world_transform.matrix() * glm::vec4(0, 1.0f, 0, 1);
    obj1->texture_unit = 2;

    part_list.push_back(obj1);


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


    for (auto obj : part_list) {

        obj->animate(time, delta_time);

        auto model_transform = obj->animation_transform.matrix() * obj->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        glUniform1i(sampler_loc, obj->texture_unit);

        glDrawArrays(GL_TRIANGLES, obj->the_shape->buffer_start, obj->the_shape->buffer_size);
    }
}


int
main(int argc, char** argv)
{
    glfwInit();
    auto aspect_ratio = 16.0/9.0;
    auto* window = cs4722::setup_window("Texture on Shape", 0.9, aspect_ratio);
    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();
    init();
    the_view->perspective_aspect = aspect_ratio;

    /*
     *   Use one of the texture utilities to load a texture from a file.
     *   Check the API: http://ksuweb.kennesaw.edu/~bsetzer/4722sp21/nanoc/output/references/html/texture__utilities_8h.html
     */
    cs4722::init_texture_from_file("../media/tulips-bed-2048x2048.png", 2);

    glfwSetWindowUserPointer(window, the_view);
    cs4722::setup_user_callbacks(window);

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
