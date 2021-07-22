


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

    cs4722::init_texture_from_file("../media/galaxy.jpg", 1);
    cs4722::init_texture_from_file("../media/coco.jpg", 2);
    cs4722::init_texture_from_file("../media/dough.jpg", 3);
    cs4722::init_texture_from_file("../media/dough2.jpg", 4);
    cs4722::init_texture_computed(1, 128);

    auto number = 2;
    auto d = 4.0f / (2 * number + 1);
    auto radius = d / 4;
    auto base = -1 + 3 * radius;
    auto center = glm::vec3(base + 1 * d, base + 1 * d, base + 1 * d);

    auto* torus = new cs4722::torus();
    torus->color_set_ = std::vector({cs4722::x11::goldenrod1, cs4722::x11::black});

    auto* object1 = new cs4722::part_rotating();
    object1->the_shape = torus;
    object1->world_transform.translate = center + glm::vec3(0, 0, .25);
    object1->world_transform.scale = glm::vec3(radius, radius, radius);
    object1->animation_transform.rotation_axis = glm::vec3(0, 0, 1);
    object1->animation_transform.rotation_angle = 0;
    object1->animation_transform.rotation_center =
            object1->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));
    object1->rotation_rate = M_PI / 3;
    object1->texture_unit= 3;
    part_list.push_back(object1);

    auto* object2 = new cs4722::part_rotating();
    object2->the_shape = torus;
    object2->world_transform.translate = center + glm::vec3(0, 0, 0);
    object2->world_transform.scale = glm::vec3(radius, radius, radius);
    object2->animation_transform.rotation_axis = glm::vec3(0, 0, 1);
    object2->animation_transform.rotation_angle = 0;
    object2->animation_transform.rotation_center =
            object2->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));
    object2->rotation_rate = M_PI / 3;
    object2->texture_unit= 4;
    part_list.push_back(object2);

    cs4722::shape* be = new cs4722::sphere(15, 50);
    auto* parte = new cs4722::part_rotating();
    parte->the_shape = (be);
    parte->world_transform.translate = (glm::vec3(-.5, -.5, 0));
    parte->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    parte->rotation_rate = (M_PI / 3);
    parte->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    parte->animation_transform.rotation_center =
            parte->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    /*
     * Each part can be assigned a texture unit, this is used in the display function
     */
    parte->texture_unit = 1;
    parte->surface_material.diffuse_color = cs4722::x11::violet_red;
    parte->surface_effect = 1;
    part_list.push_back(parte);

    cs4722::shape* bb = new cs4722::sphere(15, 50);
    auto* part3 = new cs4722::part_rotating();
    part3->the_shape = (bb);
    part3->world_transform.translate = (glm::vec3(.5, -.5, 0));
    part3->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    part3->rotation_rate = (M_PI / 3);
    part3->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    part3->animation_transform.rotation_center =
            part3->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    /*
     * Each part can be assigned a texture unit, this is used in the display function
     */
    part3->texture_unit = 2;
    part3->surface_material.diffuse_color = cs4722::x11::rosy_brown;
    part3->surface_effect = 1;
    part_list.push_back(part3);




    cs4722::shape* b1 = new cs4722::block();
    auto* part1 = new cs4722::part_rotating();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(-.5, .5, 0));
    part1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1->rotation_rate = (M_PI / 3);
    part1->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    part1->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part1->texture_unit = 2;
    part1->surface_material.diffuse_color = cs4722::x11::slate_blue;
    part1->surface_effect = 0;
    part_list.push_back(part1);

    b1 = new cs4722::cylinder();
    part1 = new cs4722::part_rotating();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(.5, .5, 0));
    part1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1->rotation_rate = (M_PI / 3);
    part1->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    part1->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part1->texture_unit = 1;
    part1->surface_material.diffuse_color = cs4722::x11::olive_drab;
    part1->surface_effect = 2;
    part_list.push_back(part1);

    cs4722::shape* bbb = new cs4722::block();
    auto* part4 = new cs4722::part_rotating();
    part4->the_shape = (bbb);
    part4->world_transform.translate = (glm::vec3(-.75, .5, 0));
    part4->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part4->rotation_rate = (M_PI / 3);
    part4->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    part4->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part4->texture_unit = 1;
    part4->surface_material.diffuse_color = cs4722::x11::slate_blue;
    part4->surface_effect = 0;
    part_list.push_back(part4);

    b1 = new cs4722::cylinder();
    part1 = new cs4722::part_rotating();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(.5, .5, 0));
    part1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1->rotation_rate = (M_PI / 3);
    part1->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    part1->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part1->texture_unit = 1;
    part1->surface_material.diffuse_color = cs4722::x11::olive_drab;
    part1->surface_effect = 2;
    part_list.push_back(part1);

    b1 = new cs4722::cylinder();
    part1 = new cs4722::part_rotating();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(.75, .75, 0));
    part1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1->rotation_rate = (M_PI / 3);
    part1->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    part1->animation_transform.rotation_center =
            part1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part1->texture_unit = 1;
    part1->surface_material.diffuse_color = cs4722::x11::indian_red;
    part1->surface_effect = 2;
    part_list.push_back(part1);


    cs4722::shape* b1e = new cs4722::block();
    auto* part1e = new cs4722::part_rotating();
    part1e->the_shape = (b1e);
    part1e->world_transform.translate = (glm::vec3(-.5, 0, 0));
    part1e->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    part1e->rotation_rate = (M_PI / 3);
    part1e->world_transform.scale = (glm::vec3(.2f, .6f, .2f));
    part1e->animation_transform.rotation_center =
            part1e->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    part1e->texture_unit = 2;

    part_list.push_back(part1e);


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
