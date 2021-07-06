

#include "sharing.h"


static cs4722::view *the_view;
static GLuint program;
/*
 * The two parts of the scene use different buffers.
 * There is a Vertex Array Object associated with each set of buffers (returned by
 *  init_buffers)
 * The associated VAO will be bound in the display function in order to activate the
 * appropriate set of buffers.
 */
static GLuint vao;
static std::vector<cs4722::part*> part_list;


GLuint sampler_loc, transform_loc;

static void init(int environment_unit) {


    program = cs4722::load_shaders("skybox_vertex_shader02.glsl","skybox_fragment_shader02.glsl");
    glUseProgram(program);

    sampler_loc = glGetUniformLocation(program, "sampler");
    transform_loc = glGetUniformLocation(program, "transform");


    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // size of the skybox: we'll vary the scale to see the effect
    auto skybox_scale = 40.0f;
	
    auto* a_shape = new cs4722::block();
    // auto* a_shape = new cs4722::sphere();
    // auto* a_shape = new cs4722::cylinder();
    // auto* a_shape = new cs4722::torus();

    auto* a_part = new cs4722::part();
    a_part->the_shape = (a_shape);
    a_part->world_transform.scale = glm::vec3(skybox_scale);
    a_part->texture_unit = environment_unit;

    part_list.push_back(a_part);

    // same as usual but store the return value: a VAO identifier
    vao = cs4722::init_buffers(program, part_list, "bPosition");
}

void skybox_display()
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


    for(auto *obj: part_list) {


        auto model_transform = obj->animation_transform.matrix() * obj->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        glUniform1i(sampler_loc, obj->texture_unit);

        glUniform1i(sampler_loc, obj->texture_unit);
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawArrays(GL_TRIANGLES, obj->the_shape->buffer_start,
                     obj->the_shape->buffer_size);

    }
}


void skybox_setup(cs4722::view *a_view) {
    the_view = a_view;


    auto environment_unit = 77;
    /*
     * utility function that loads a cube texture from six files stored in a specified directory.
     *
     * first parameter is the path to the directory with the files
     * second parameter is the texture unit to use for this texture and sampler
     * third parameter is the file extension
     */
    cs4722::init_cube_texture_from_path("../media/fjaderholmarna", environment_unit, "png");

    init(environment_unit);
}
