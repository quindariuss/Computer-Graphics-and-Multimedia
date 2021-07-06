

#include <GLM/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>


#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/callbacks.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/load_shaders.h"

static GLuint program;
static auto* the_view = new cs4722::view();
static std::vector<cs4722::part*> parts_list;
GLuint  vao;

static GLuint transform_loc;
static GLuint sampler_loc;


/*
 * Just for this example, we add a shape consisting of a set of points.
 * This is convenient, especially using the buffer utilities and parts.
 */
class points_shape : public cs4722::shape
{
public:

    /**
     * Store a list of positions of the points
     */
	std::vector<glm::vec4> *position_list;

	/**
	 *  Intialize the list of points to empty.
	 *  Also set the drawing mode to POINTS
	 */
	points_shape()
		: position_list(new std::vector<glm::vec4>())
	{
		drawing_mode = GL_POINTS;
	}

	/**
	 * Return the list of positions.
	 * @return
	 */
	std::vector<glm::vec4>* positions() override
	{
		return position_list;
	}

	/**
	 * Return an empty list
	 */
	std::vector<cs4722::color>* colors() override
	{
		return new std::vector<cs4722::color>();
	}
    /**
     * Return an empty list
     */

	std::vector<glm::vec2>* texture_coordinates() override
	{
		return new std::vector<glm::vec2>();
	}

    /**
     * Return an empty list
     */
	std::vector<glm::vec4>* normals() override
	{
		return new std::vector<glm::vec4>();
	}

	/**
	 * The number of positions is the number of vertices for this 'shape'.
	 */
	int get_size() override
	{
		return position_list->size();
	}
	
};


void init()
{

	program = cs4722::load_shaders("vertex_shader06.glsl",
                                 "fragment_shader06.glsl");
//	auto pr = program;
	glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");
    sampler_loc = glGetUniformLocation(program, "sampler");


    glPointSize(100);
	// the following is needed to enable point sprites.
	//  Actually, it enables using gl_PointCoord in the fragment shader.
	// Either this setting should not be needed
	//      OR an appropriate symbolic constant should be defined.
	// But, no such luck
	glEnable(0x8861);


//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	the_view->set_flup(glm::vec3(-0.352275, -7.45058e-09, -0.935897),
		glm::vec3(-0.935897, 0, 0.352274),
		glm::vec3(5.85944e-08, 1, 1.20934e-08),
		glm::vec3(1.34801, 0.785008, 3.00568));

	auto num_groups = 15;
	auto num_points_per_group = 3;
	auto min_c = -2.0;
	auto max_c = 2.0;

	for (int group = 0; group < num_groups; group++)
	{

		auto* b = new points_shape();

		for (int i = 0; i < num_points_per_group; i++)
		{
			auto x = glm::linearRand(min_c, max_c);
			auto y = glm::linearRand(min_c, max_c);
			auto z = glm::linearRand(min_c, max_c);
			b->position_list->push_back(glm::vec4(x, y, z, 1));
		}

		// auto* obj = new object_random_walk();
		auto* part = new cs4722::part_rotating();

		
		auto cx = glm::linearRand(min_c, max_c);
		auto cy = glm::linearRand(min_c, max_c);
		auto cz = glm::linearRand(min_c, max_c);
        part->animation_transform.rotation_center = glm::vec3(cx, cy, cz);

        part->the_shape = b;
        part->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
        part->rotation_rate = M_PI / 3;
        part->texture_unit = group % 3;
		parts_list.push_back(part);
	}

	auto pl = parts_list;

	vao = cs4722::init_buffers(program, parts_list, "bPosition");

}



void display()
{

    glBindVertexArray(vao);
    glUseProgram(program);

    static auto last_time = 0.0;
    auto *tv = the_view;

    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect, the_view->perspective_near);
    auto vp_transform = projection_transform * view_transform;


    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;


    for (auto obj : parts_list) {
         obj->animate(time, delta_time);

        auto model_transform = obj->animation_transform.matrix() * obj->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        glUniform1i(sampler_loc, obj->texture_unit);

        glDrawArrays(obj->the_shape->drawing_mode, obj->the_shape->buffer_start, obj->the_shape->buffer_size);
    }
}


int
main(int argc, char** argv)
{
	glfwInit();


    auto *window = cs4722::setup_window("Point Sprites", .9);

    gladLoadGL(glfwGetProcAddress);
	// gladLoadGL();
	cs4722::setup_debug_callbacks();

	the_view->set_camera_position(glm::vec3(0, 0, 1));

	
	init();

    cs4722::init_texture_from_file("../media/sprite.png", 1);
    cs4722::init_texture_from_file("../media/sprite2.png", 2);
    cs4722::init_texture_computed(0);


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
