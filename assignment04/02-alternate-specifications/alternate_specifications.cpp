



#include "GLM/gtc/type_ptr.hpp"
#include "GLM/geometric.hpp"

#include <glad/gl.h>


#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/load_shaders.h"
#include "cs4722//part_elliptical_orbit.h"

static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::part*> part_list;

static GLuint transform_loc;



void init()
{

    the_view = new cs4722::view();
    the_view->camera_position = glm::vec3(0, 0, 3);
//    the_view->set_flup(glm::vec3(-0.0685846,-0.968715,-0.23851), glm::vec3(-0.961055,0,0.276356),   glm::vec3(-0.26771,0.248175,-0.930989),  glm::vec3(0.161839,4.46484,2.75902));
    the_view->set_flup(glm::vec3(1,0,0), glm::vec3(0,0,-1), glm::vec3(0,1,0), glm::vec3(-3,0,0));
    the_view->enable_logging = false;

    program = cs4722::load_shaders("02-vertex_shader.glsl","02-fragment_shader.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");



    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    /************************************
     * Start data block
     ***************/

    // unit vectors for A and P and length given
    auto rsqrt3 = 1.0 / sqrt(3.0);
    auto rsqrt2 = 1.0 / sqrt(2.0);
    auto p1_unit_a = glm::vec3(rsqrt3, rsqrt3, rsqrt3);
    auto p1_unit_p = glm::vec3(rsqrt2, -rsqrt2, 0);
    auto p1_semi_major_axis = 3.0f;
    auto p1_semi_minor_axis = 2.0f;
    auto p1_orbital_rate = 2 * M_PI / 5;
    auto p1_path_center = glm::vec3(0,0,0);
    auto p1_time_offset = 2.5;

    // non-unit vectors for A and P, length given
    auto p2_non_unit_a = glm::vec3(-1, 1, 1);
    auto p2_non_unit_p = glm::vec3(2, 1, 1);
    auto p2_semi_major_axis = 3.0f;
    auto p2_semi_minor_axis = .5f;
    auto p2_orbital_rate = 2 * M_PI / 10;
    auto p2_path_center = glm::vec3(0,0,0);
    auto p2_time_offset = 7;


    // normal and non-unit P with lengths
    auto p3_normal = glm::vec3(0,0, 1);
    auto p3_non_unit_p = glm::vec3(1, 0, 0);
    auto p3_semi_major_axis = 2.5f;
    auto p3_semi_minor_axis = 2.0f;
    auto p3_orbital_rate = 2 * M_PI / 12;
    auto p3_path_center = glm::vec3(0,0,0);
    auto p3_time_offset = 7;


    // normal and non-unit P with lengths, period for orbital rate
    auto p4_normal = glm::vec3(0,1, 0);
    auto p4_non_unit_p = glm::vec3(1, 0, 0);
    auto p4_semi_major_axis = 4.0f;
    auto p4_semi_minor_axis = 2.5f;
    auto p4_orbital_period = 15;
    auto p4_path_center = glm::vec3(0,0,0);
    auto p4_time_offset = 7;


    // normal and non-unit P with lengths, period for orbital rate, position of focus
    auto p5_normal = glm::vec3(1,0, 0);
    auto p5_non_unit_p = glm::vec3(0, 0, 1);
    auto p5_semi_major_axis = 3.0f;
    auto p5_semi_minor_axis = 2.0f;
    auto p5_orbital_period = 8;
    auto p5_path_focus = glm::vec3(0,0,0);
    auto p5_time_offset = 7;

    /************************************
     * End data block
     ***************/



    cs4722::shape* b1 = new cs4722::sphere(15, 50);
    b1->color_set_ = std::vector({cs4722::x11::goldenrod1, cs4722::x11::goldenrod4});
    auto* p1 = new cs4722::part_elliptical_orbit();
    p1->the_shape = b1;
    p1->world_transform.scale = (glm::vec3(.5, .5, .5));
    p1->path_center = p1_path_center;
    p1->orbital_rate = p1_orbital_rate;

    p1-> aphelion_vector = p1_unit_a * p1_semi_major_axis;
     p1->perihelion_vector = p1_unit_p * p1_semi_minor_axis;

   p1->rotation_rate = M_PI/2 ;
   p1->world_transform.translate = glm::vec3 (.5,-.5,0);
   p1->animation_transform.rotation_axis = p1->world_transform.matrix() * glm::vec4(0,1,0,0);
   p1->animation_transform.rotation_center = p1->world_transform.matrix() * glm::vec4(0,0,0,1);



    p1->time_offset = p1_time_offset;part_list.push_back(p1);


    cs4722::shape* b2 = new cs4722::sphere(15, 50);
    b2->color_set_ = std::vector({cs4722::x11::olive_drab1, cs4722::x11::olive_drab4});
    auto* p2 = new cs4722::part_elliptical_orbit();
    p2->the_shape = b2;
    p2->world_transform.scale = (glm::vec3(.5, .5, .5));
    p2->path_center = p2_path_center;
    p2->orbital_rate = p2_orbital_rate;
    p2->time_offset = p2_time_offset;part_list.push_back(p2);

    p2-> aphelion_vector = glm::normalize(p2_non_unit_a) * p2_semi_major_axis;
    p2-> perihelion_vector = glm::normalize(p2_non_unit_p) * p2_semi_minor_axis;

    p2->rotation_rate = M_PI/2 ;
    p2->world_transform.translate = glm::vec3 (.5,-.5,0);
    p2->animation_transform.rotation_axis = p2->world_transform.matrix() * glm::vec4(0,1,0,0);
    p2->animation_transform.rotation_center = p2->world_transform.matrix() * glm::vec4(0,0,0,1);
    part_list.push_back(p2);




    cs4722::shape* b3 = new cs4722::sphere(15, 50);
    b3->color_set_ = std::vector({cs4722::x11::steel_blue1, cs4722::x11::steel_blue4});
    auto* p3 = new cs4722::part_elliptical_orbit();
    p3->the_shape = b3;
    p3->world_transform.scale = (glm::vec3(.5, .5, .5));
    p3->path_center = p3_path_center;
    p3->orbital_rate = p3_orbital_rate;
    p3->time_offset = p3_time_offset;part_list.push_back(p3);
    p3-> aphelion_vector= glm::normalize(glm::cross(p3_non_unit_p,p3_normal)) * p3_semi_major_axis;
    p3-> perihelion_vector = glm::normalize(p3_non_unit_p) * p3_semi_minor_axis;

    p3->rotation_rate = M_PI/2 ;
    p3->world_transform.translate = glm::vec3 (.5,-.5,0);
    p3->animation_transform.rotation_axis = p3->world_transform.matrix() * glm::vec4(0,1,0,0);
    p3->animation_transform.rotation_center = p3->world_transform.matrix() * glm::vec4(0,0,0,1);

    part_list.push_back(p3);

    cs4722::shape* b4 = new cs4722::sphere(15, 50);
    b4->color_set_ = std::vector({cs4722::x11::violet_red1, cs4722::x11::violet_red4});
    auto* p4 = new cs4722::part_elliptical_orbit();
    p4->the_shape = b4;
    p4->world_transform.scale = (glm::vec3(.5, .5, .5));
    p4-> aphelion_vector= glm::normalize(glm::cross(p4_non_unit_p,p4_normal)) * p4_semi_major_axis;
    p4-> perihelion_vector = glm::normalize(p4_non_unit_p) * p4_semi_minor_axis;
    p4->orbital_rate = 2 * M_PI / p4_orbital_period;
    p4-> path_center = p4_path_center;
    p4->time_offset = p4_time_offset;

    p4->rotation_rate = M_PI/2 ;
    p4->world_transform.translate = glm::vec3 (.5,-.5,0);
    p4->animation_transform.rotation_axis = p4->world_transform.matrix() * glm::vec4(0,1,0,0);
    p4->animation_transform.rotation_center = p4->world_transform.matrix() * glm::vec4(0,0,0,1);

    part_list.push_back(p4);


    cs4722::shape* b5 = new cs4722::sphere(15, 50);
    b5->color_set_ = std::vector({cs4722::x11::cyan1, cs4722::x11::cyan2});
    auto* p5 = new cs4722::part_elliptical_orbit();
    p5->the_shape = b5;
    p5->world_transform.scale = (glm::vec3(.5, .5, .5));
    p5-> aphelion_vector= glm::normalize(glm::cross(p5_non_unit_p,p5_normal)) * p5_semi_major_axis;
    p5-> perihelion_vector = glm::normalize(p5_non_unit_p) * p5_semi_minor_axis;
    p5->orbital_rate = 2 * M_PI / p5_orbital_period;
    p5->rotation_rate = M_PI/2 ;
    p5->world_transform.translate = glm::vec3 (.5,-.5,0);
    p5->animation_transform.rotation_axis = p5->world_transform.matrix() * glm::vec4(0,1,0,0);
    p5->animation_transform.rotation_center = p5->world_transform.matrix() * glm::vec4(0,0,0,1);
    auto norm  = glm::normalize(glm::cross(p5_non_unit_p, p5_normal));
    float gravity = sqrt(p5_semi_major_axis *  p5_semi_major_axis - p5_semi_minor_axis * p5_semi_minor_axis);
    p5-> path_center = p5_path_focus - (norm  - gravity);
    p5->rotation_rate = M_PI/2 ;
    p5->world_transform.translate = glm::vec3 (.5,-.5,0);
    p5->animation_transform.rotation_axis = p5->world_transform.matrix() * glm::vec4(0,1,0,0);
    p5->animation_transform.rotation_center = p5->world_transform.matrix() * glm::vec4(0,0,0,1);
    part_list.push_back(p5);
    auto *partC = new cs4722::part();
    partC->the_shape = new cs4722::sphere();
    partC->the_shape->color_set_ = std::vector({cs4722::x11::wheat1, cs4722::x11::wheat4});
    partC->world_transform.scale = glm::vec3(.2);
    partC->world_transform.translate = glm::vec3(0);
    part_list.push_back(partC);


    auto *partC2 = new cs4722::part();
    partC2->the_shape = new cs4722::sphere();
    partC2->the_shape->color_set_ = std::vector({cs4722::x11::white, cs4722::x11::white});
    partC2->world_transform.scale = glm::vec3(.2);
    partC2->world_transform.translate = p5->path_center;
    part_list.push_back(partC2);





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
