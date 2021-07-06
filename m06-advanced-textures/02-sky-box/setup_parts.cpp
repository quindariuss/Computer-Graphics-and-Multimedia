


#include "sharing.h"

static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::part*> part_list;

static GLuint transform_loc;
static GLuint sampler_loc;

static GLuint vao;


void parts_setup(cs4722::view* view)
{

    the_view = view;
//    the_view->enable_logging = true;
    the_view->set_flup(glm::vec3(0.202971,-0.227978,-0.952277),
                       glm::vec3(-0.978031,0,-0.20846),
                       glm::vec3(0.0475242,0.973667,-0.222969),
                       glm::vec3(-0.146291,0.195185,1.3214));
    


    program = cs4722::load_shaders("parts_vertex_shader02.glsl",
                                   "parts_fragment_shader02.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");
    sampler_loc = glGetUniformLocation(program, "sampler");

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


    cs4722::init_texture_from_file("../media/tulips-bed-2048x2048.png", 2);
    cs4722::init_texture_computed(1, 8);


    cs4722::shape* b = new cs4722::sphere(15, 50);
    auto* part = new cs4722::part_rotating();
    part->the_shape = (b);
    part->world_transform.translate = (glm::vec3(.5, -.5, 0));
    part->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    part->rotation_rate = (M_PI / 3);
    part->world_transform.scale = (glm::vec3(.4f, .6f, .4f));
    part->animation_transform.rotation_center =
            part->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
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


    vao = cs4722::init_buffers(program, part_list, "bPosition", "", "bTextureCoord");

}


//----------------------------------------------------------------------------
//
// display
//


void parts_display()
{

    // bind the VAO for this set of vertex buffers
    glBindVertexArray(vao);
    // since we have multiple sets of shader programs, we must activate the one we want to use
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


    for (auto part : part_list) {
        part->animate(time, delta_time);
        auto model_transform = part->animation_transform.matrix() * part->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        glUniform1i(sampler_loc, part->texture_unit);
        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
    }
}
