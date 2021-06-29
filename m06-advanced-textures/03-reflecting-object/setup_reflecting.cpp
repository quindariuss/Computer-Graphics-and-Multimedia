
#include <GLM/gtc/matrix_inverse.hpp>

#include "sharing.h"



static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::part*> part_list;

static GLuint transform_loc, n_transform_loc, mv_transform_loc;
static GLuint sampler_loc;

static GLuint vao;

//static GLuint cube_texture_unit;


void reflecting_setup(cs4722::view* view, GLuint cube_texture_unit)
{

    the_view = view;

    program = cs4722::load_shaders("reflecting_vertex_shader03.glsl",
                                   "reflecting_fragment_shader03.glsl");
    glUseProgram(program);


    transform_loc = glGetUniformLocation(program, "transform");
    mv_transform_loc = glGetUniformLocation(program, "mv_transform");
    n_transform_loc = glGetUniformLocation(program, "n_transform");
    sampler_loc = glGetUniformLocation(program, "sampler");

    glUniform1i(sampler_loc, cube_texture_unit);



    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


    cs4722::shape* b = new cs4722::sphere(15, 50);
    auto* obj = new cs4722::part_rotating();
    obj->the_shape = (b);
    obj->world_transform.translate = (glm::vec3(.5, 5, 0));
    obj->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    obj->rotation_rate = (M_PI / 3);
    obj->world_transform.scale = (glm::vec3(.4f, .6f, .4f));
    obj->animation_transform.rotation_center =
            obj->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
//    obj->texture_unit = 1;
    part_list.push_back(obj);


    cs4722::shape* b1 = new cs4722::block();
    auto* obj1 = new cs4722::part_rotating();
    obj1->the_shape = (b1);
    obj1->world_transform.translate = (glm::vec3(-.5, 0, 3));
    obj1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    obj1->rotation_rate = (M_PI / 3);
    obj1->world_transform.scale = (glm::vec3(.2f, .6f, .2f));
    obj1->animation_transform.rotation_center =
            obj1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
//    obj1->texture_unit = 2;

    part_list.push_back(obj1);


    vao = cs4722::init_buffers(program, part_list, "bPosition", "", "", "bNormal");
}


void reflecting_display()
{

    glBindVertexArray(vao);
    glUseProgram(program);

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
        auto mv_transform = view_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        glUniformMatrix4fv(mv_transform_loc, 1, GL_FALSE, glm::value_ptr(mv_transform));
        glUniformMatrix4fv(n_transform_loc, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(mv_transform)));
        glDrawArrays(GL_TRIANGLES, obj->the_shape->buffer_start, obj->the_shape->buffer_size);
    }
}
