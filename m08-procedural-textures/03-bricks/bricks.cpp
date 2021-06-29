


#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_inverse.hpp>

#include <iostream>


#include <glad/gl.h>

#include <GLFW/glfw3.h>


#include "cs4722/view.h"
#include "cs4722/x11.h"
#include "cs4722/shape.h"
#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/callbacks.h"
#include "cs4722/light.h"
#include "cs4722/load_shaders.h"

static cs4722::view *the_view;
static GLuint program;
static GLuint vao;

static GLuint ambient_light_loc;
static GLuint specular_light_loc;
static GLuint diffuse_light_loc;
static GLuint ambient_color_loc;
static GLuint specular_color_loc;
static GLuint diffuse_color_loc;
static GLuint light_position_loc;
static GLuint specular_shininess_loc;     // exponent for sharpening highlights
static GLuint specular_strength_loc;      // extra factor to adjust shininess
static GLuint brick_size_loc;
static GLuint brick_pct_loc;


static GLuint mv_transform_loc;
static GLuint p_transform_loc;
static GLuint normal_transform_loc;



static std::vector<cs4722::part*> parts_list;

static cs4722::light a_light;

static auto brick_size = glm::vec2(.2, .1);
static auto brick_pct = glm::vec2(.8, .8);



void init()
{
    the_view = new cs4722::view();
    the_view->enable_logging = false;
    a_light.ambient_light = cs4722::x11::gray25;
    a_light.light_direction_position = glm::vec4(0, 5, 5, 1);
        ///< in world coordinates

	program = cs4722::load_shaders("vertex_shader03.glsl",
                                   "fragment_shader03.glsl");
	glUseProgram(program);
	auto pr = program;



    // fragment shader uniformas
    ambient_light_loc = glGetUniformLocation(program, "ambient_light");
    specular_light_loc = glGetUniformLocation(program, "specular_light");
    diffuse_light_loc = glGetUniformLocation(program, "diffuse_light");
    ambient_color_loc = glGetUniformLocation(program, "ambient_color");
    specular_color_loc = glGetUniformLocation(program, "specular_color");
    diffuse_color_loc = glGetUniformLocation(program, "diffuse_color");
    light_position_loc = glGetUniformLocation(program, "light_position");
    specular_shininess_loc = glGetUniformLocation(program, "specular_shininess");
    specular_strength_loc = glGetUniformLocation(program, "specular_strength");
//    auto all = ambient_light_loc;
//    auto sll = specular_light_loc;
//    auto dll = diffuse_light_loc;
//    auto acl = ambient_color_loc;
//    auto dcl = diffuse_color_loc;
//    auto scl = specular_color_loc;
//    auto lpl = light_position_loc;
//    auto ssl = specular_shininess_loc;
//    auto srl = specular_strength_loc;
    // vertex shader uniforms
    mv_transform_loc = glGetUniformLocation(program, "mv_transform");
//    v_transform_loc = glGetUniformLocation(program, "v_transform");
    p_transform_loc = glGetUniformLocation(program, "p_transform");
    normal_transform_loc = glGetUniformLocation(program, "normal_transform");
    brick_size_loc = glGetUniformLocation(program, "brick_size");
    brick_pct_loc = glGetUniformLocation(program, "brick_pct");

//    auto mtl = mv_transform_loc;
//    auto ptl = p_transform_loc;
//    auto ntl = normal_transform_loc;
//    auto wdl = width_loc;
//    auto fzl = fuzz_loc;
//    auto sl = scale_loc;





    glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);


	// create a list of shapes that will be shared by the objects we have

	const auto color_set = std::vector <cs4722::color>({
			cs4722::x11::white, cs4722::x11::grey50, cs4722::x11::grey75,
		});
	
	auto* shape_list = new std::vector<cs4722::shape*>();
	shape_list->push_back(new cs4722::sphere());
	shape_list->push_back(new cs4722::block());
	shape_list->push_back(new cs4722::torus());
	shape_list->push_back(new cs4722::cylinder());
	auto numshp = shape_list->size();



	auto number = 4;
	auto d = 20.0f / (2 * number + 1);
	auto radius = d / 4;
	auto base = -number * d / 2 + radius;

	for (auto x = 0; x < number; ++x)
	{
		for (auto y = 0; y < number; ++y)
		{
			for (auto z = 0; z < number; ++z)
			{
				auto* obj = new cs4722::part_rotating();
				obj->the_shape = (shape_list->at((x + y + z) % numshp));
				obj->world_transform.translate = (glm::vec3(base + x * d, base + y * d, base + z * d));
				obj->world_transform.scale = (glm::vec3(radius, radius, radius));
                obj->animation_transform.rotation_axis = (glm::vec3(x + 1, y + 1, z + 1));
                obj->animation_transform.rotation_center =
                        obj->world_transform.matrix() * glm::vec4(0,0,0,1);
                obj->rotation_rate = ((x + y + z) % 12 * M_PI / 24);
				obj->surface_material.ambient_color = (cs4722::color(
					x * 255 / (number-1), y * 255 / (number - 1), 
					z * 255 / (number - 1), 255));
				obj->surface_material.specular_color = cs4722::x11::white;
				obj->surface_material.diffuse_color = obj->surface_material.ambient_color;
				obj->surface_material.specular_strength = 30.0;
				obj->surface_material.shininess = 15.0;
				parts_list.push_back(obj);
			}
		}
	}
	
//    fprintf(stderr, "init_buffers to start\n");
    vao = cs4722::init_buffers(program, parts_list, "bPosition","",
                               "","bNormal");
//    fprintf(stderr, "init_buffers done\n");
}



void display()
{
    static auto last_time = 0.0;

    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glBindVertexArray(vao);
    glUseProgram(program);

    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect,
                                                         the_view->perspective_near);

    glUniform4fv(light_position_loc, 1,
                 glm::value_ptr(view_transform * a_light.light_direction_position));
    glUniform4fv(ambient_light_loc, 1, a_light.ambient_light.as_float());
    glUniform4fv(diffuse_light_loc, 1, a_light.diffuse_light.as_float());
    glUniform4fv(specular_light_loc, 1, a_light.specular_light.as_float());
    glUniform2fv(brick_pct_loc, 1, glm::value_ptr(brick_pct));
    glUniform2fv(brick_size_loc, 1, glm::value_ptr(brick_size));


    auto time = glfwGetTime();
	auto delta_time = time - last_time;

	for (auto obj: parts_list) {

		obj->animate(time, delta_time);
        auto mv_transform = view_transform *
                obj->animation_transform.matrix() * obj->world_transform.matrix();

        glUniformMatrix4fv(mv_transform_loc, 1, GL_FALSE, glm::value_ptr(mv_transform));
        glUniformMatrix4fv(p_transform_loc, 1, GL_FALSE, glm::value_ptr(projection_transform));
        glUniformMatrix4fv(normal_transform_loc, 1, GL_FALSE,
                           glm::value_ptr(glm::inverseTranspose(mv_transform)));

        glm::vec4 ambient_product = *a_light.ambient_light.as_vec4()
                * *obj->surface_material.ambient_color.as_vec4();
        glm::vec4 diffuse_product = *a_light.diffuse_light.as_vec4()
                                    * *obj->surface_material.diffuse_color.as_vec4();
        glm::vec4 specular_product = *a_light.specular_light.as_vec4()
                                    * *obj->surface_material.specular_color.as_vec4();

        glUniform4fv(ambient_color_loc, 1, obj->surface_material.ambient_color.as_float());
        glUniform4fv(diffuse_color_loc, 1, obj->surface_material.diffuse_color.as_float());
        glUniform4fv(specular_color_loc, 1, obj->surface_material.specular_color.as_float());
        glUniform1f(specular_shininess_loc, obj->surface_material.shininess);
        glUniform1f(specular_strength_loc, obj->surface_material.specular_strength);


        glDrawArrays(GL_TRIANGLES, obj->the_shape->buffer_start,
			obj->the_shape->buffer_size);
		
	}
}




int
main(int argc, char** argv)
{
	glfwInit();
	auto *window = cs4722::setup_window("No Lighting", 0.9);
    gladLoadGL(glfwGetProcAddress);
	cs4722::setup_debug_callbacks();

	init();

	glfwSetWindowUserPointer(window, the_view);
	cs4722::setup_user_callbacks(window);

	while (!glfwWindowShouldClose(window))
	{
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray25.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);

        display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}
