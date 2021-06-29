


#include "GLM/glm.hpp"
#include "GLM/ext.hpp"


#include <algorithm>


#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/load_shaders.h"

static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::part*> part_list;

static GLuint transform_loc;


void init()
{

    the_view = new cs4722::view();


    the_view->camera_position = glm::vec3(0, 0, 2);
    // the_scene->the_view->camera_up = glm::vec3(0, -1, 0);
    // the_scene->the_view->camera_up = glm::vec3(1, -1, 0);
    // the_scene->the_view->camera_position = glm::vec3(0, 0, 1);
    // the_scene->the_view->camera_forward = glm::vec3(0, 18, -1);


    the_view->perspective_aspect = 1.0;
    the_view->perspective_fovy = M_PI / 2;
    the_view->perspective_near = .1;


    program = cs4722::load_shaders("vertex_shader.glsl","fragment_shader.glsl");

    glUseProgram(program);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    transform_loc = glGetUniformLocation(program, "transform");


    // create a shape
    //cs4722::shape *b =  new cs4722::cylinder(.75, 20);
    cs4722::shape* b = new cs4722::sphere(15, 50);
    // cs4722::shape* b = new cs4722::block();
    auto* part = new cs4722::part_rotating();
    part->the_shape = (b);
    part->world_transform.translate = (glm::vec3(.5, -.5, 0));
    part->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    part->rotation_rate = (M_PI / 3);
    part->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    part->animation_transform.rotation_center =
            part->world_transform.matrix() * glm::vec4(0, 0, 0, 1);

    part_list.push_back(part);


    cs4722::shape* b1 = new cs4722::block();
    auto* part1 = new cs4722::part_rotating();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(-.5, 0, 0));
    part1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1->rotation_rate = (M_PI / 3);
    part1->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part1->world_transform.scale = (glm::vec3(.2f, .6f, .2f));

    part_list.push_back(part1);

    cs4722::init_buffers(program, part_list, "bPosition", "bColor");

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

        auto transform = vp_transform * part->animation_transform.matrix() *
                         part->world_transform.matrix();
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
    }
}

int main(int argc, char** argv)
{
    glfwInit();


    /*
     * We can set the window aspect ratio when creating it.
     *  -  start with 1.0
     *  -  then try 2.0 and notice the distortion
     *  - change the perspective aspect in the view to match the aspect ratio
     *  - changing window size does not have any effect on the sizing of the scene
     */
    auto aspect_ratio = 1.0;
    auto *window = cs4722::setup_window("Projection with View", 0.9, aspect_ratio);

    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();

    init();
//    the_view->perspective_aspect = aspect_ratio;

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
