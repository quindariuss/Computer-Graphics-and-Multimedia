



#include "GLM/gtc/type_ptr.hpp"

#include <glad/gl.h>


#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/load_shaders.h"
#include "cs4722//part_elliptical_orbit.h"

static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::part*> object_list;

static GLuint transform_loc;



void init()
{

    the_view = new cs4722::view();
    the_view->camera_position = glm::vec3(0, 0, 3);
//    the_view->set_flup(glm::vec3(-0.0685846,-0.968715,-0.23851), glm::vec3(-0.961055,0,0.276356),   glm::vec3(-0.26771,0.248175,-0.930989),  glm::vec3(0.161839,4.46484,2.75902));
    the_view->enable_logging = false;

    program = cs4722::load_shaders("01-vertex_shader.glsl","01-fragment_shader.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");



    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


    auto a_vec = glm::vec3(2,2,0);
    auto p_vec = glm::vec3(0, 0, 2);
    auto center = glm::vec3(1,1,1);
    
    cs4722::shape* b = new cs4722::sphere(15, 50);
    auto* part = new cs4722::part_elliptical_orbit();
    part->the_shape = (b);
//    part->world_transform.translate = (glm::vec3(.5, -.5, 0));
    part->animation_transform.rotation_axis = (glm::vec3(0, 1, 0));
    part->world_transform.scale = (glm::vec3(.5, .5, .5));
    part->animation_transform.rotation_center =
            part->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    part->rotation_rate = (M_PI / 3);
    part->orbital_rate = M_PI / 5;
    part->aphelion_vector = a_vec;
    part->perihelion_vector = p_vec;
    part->path_center = center;

    object_list.push_back(part);


    auto *partC = new cs4722::part();
    partC->the_shape = new cs4722::sphere();
    partC->the_shape->color_set_ = std::vector({cs4722::x11::goldenrod1, cs4722::x11::goldenrod4});
    partC->world_transform.scale = glm::vec3(.2);
    partC->world_transform.translate = center;
    object_list.push_back(partC);



    auto sp = new cs4722::sphere();
    sp->color_set_ = std::vector({cs4722::x11::steel_blue1, cs4722::x11::steel_blue4});


    partC = new cs4722::part();
    partC->the_shape = sp;
    partC->world_transform.scale = glm::vec3(.1);
    partC->world_transform.translate = a_vec + center;
    object_list.push_back(partC);

    partC = new cs4722::part();
    partC->the_shape = sp;
    partC->world_transform.scale = glm::vec3(.1);
    partC->world_transform.translate = -a_vec + center;
    object_list.push_back(partC);

    partC = new cs4722::part();
    partC->the_shape = sp;
    partC->world_transform.scale = glm::vec3(.1);
    partC->world_transform.translate = p_vec + center;
    object_list.push_back(partC);

    partC = new cs4722::part();
    partC->the_shape = sp;
    partC->world_transform.scale = glm::vec3(.1);
    partC->world_transform.translate = -p_vec + center;
    object_list.push_back(partC);



    cs4722::shape* b1 = new cs4722::block();
    auto* part1 = new cs4722::part_rotating();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(-.5, 0, 0));
    part1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1->rotation_rate = (M_PI / 3);
    part1->world_transform.scale = (glm::vec3(.2f, .6f, .2f));
    part1->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);

//    part_list.push_back(part1);


    cs4722::init_buffers(program, object_list, "bPosition", "bColor");

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


    for (auto part : object_list) {
        part->animate(time, delta_time);
        auto model_transform = part->animation_transform.matrix() * part->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));



        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
       

    }
}


int
main(int argc, char** argv)
{
    glfwInit();
    auto aspect_ratio = 16.0/9.0;
    auto* window = cs4722::setup_window("Window Events Using Library Callbacks", 0.5,
                                        aspect_ratio);
    gladLoadGL(glfwGetProcAddress);
    glDebugMessageCallback(cs4722::message_callback, nullptr);

    init();
    the_view->perspective_aspect = aspect_ratio;

    glfwSetWindowUserPointer(window, the_view);
    glfwSetKeyCallback(window, cs4722::general_key_callback);
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
