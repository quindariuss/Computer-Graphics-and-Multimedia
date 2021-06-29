



#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_inverse.hpp>

#include <iostream>


#include <glad/gl.h>

#include <GLFW/glfw3.h>



#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/callbacks.h"
#include "cs4722/light.h"
#include "cs4722/load_shaders.h"
#include "cs4722/texture_utilities.h"

static cs4722::view *the_view;
static GLuint program;
static GLuint vao;

static GLint ambient_light_loc;
static GLint specular_light_loc;
static GLint diffuse_light_loc;
static GLint ambient_color_loc;
static GLint specular_color_loc;
static GLint diffuse_color_loc;
static GLint light_direction_loc; // direction toward the light
static GLint specular_shininess_loc;     // exponent for sharpening highlights
static GLint specular_strength_loc;      // extra factor to adjust shininess
static GLint mv_transform_loc;
static GLint p_transform_loc;
static GLint normal_transform_loc;
static GLint sampler_loc;


static std::vector<cs4722::part*> parts_list;

static cs4722::light a_light;

void init()
{
    the_view = new cs4722::view();
    the_view->enable_logging = false;
    a_light.ambient_light = cs4722::x11::gray8;

	program = cs4722::load_shaders("vertex_shader07.glsl",
                                   "fragment_shader07.glsl");
	glUseProgram(program);



    // fragment shader uniformas
    ambient_light_loc = glGetUniformLocation(program, "ambient_light");
    specular_light_loc = glGetUniformLocation(program, "specular_light");
    diffuse_light_loc = glGetUniformLocation(program, "diffuse_light");
    ambient_color_loc = glGetUniformLocation(program, "ambient_color");
    specular_color_loc = glGetUniformLocation(program, "specular_color");
    diffuse_color_loc = glGetUniformLocation(program, "diffuse_color");
    light_direction_loc = glGetUniformLocation(program, "light_direction");
    specular_shininess_loc = glGetUniformLocation(program, "specular_shininess");
    specular_strength_loc = glGetUniformLocation(program, "specular_strength");
    sampler_loc = glGetUniformLocation(program, "sampler");
    // vertex shader uniforms
    mv_transform_loc = glGetUniformLocation(program, "mv_transform");
    p_transform_loc = glGetUniformLocation(program, "p_transform");
    normal_transform_loc = glGetUniformLocation(program, "normal_transform");


    glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);


	cs4722::init_texture_from_file("../media/square-2703542_960_720.jpg",0);
    cs4722::init_texture_from_file("../media/square-background-1456646_960_720.jpg",1);
    cs4722::init_texture_from_file("../media/square-background-1456650_960_720.jpg",2);
    cs4722::init_texture_from_file("../media/tulips-bed-256x256.png",3);




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
                        obj->world_transform.matrix() * glm::vec4(0,3,0,1);
                obj->rotation_rate = ((x + y + z) % 12 * M_PI / 24);
				obj->surface_material.ambient_color = (cs4722::color(
					x * 255 / (number-1), y * 255 / (number - 1), 
					z * 255 / (number - 1), 255));
				obj->surface_material.specular_color = cs4722::x11::white;
				obj->surface_material.diffuse_color = obj->surface_material.ambient_color;
				obj->surface_material.specular_strength = 30.0;
				obj->surface_material.shininess = 10.0;
				obj->texture_unit = (x + y + z) % 3;
				parts_list.push_back(obj);
			}
		}
	}
	

    vao = cs4722::init_buffers(program, parts_list, "bPosition","",
                               "bTextureCoord","bNormal");
}



void display()
{

    glBindVertexArray(vao);
    glUseProgram(program);

    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect,
                                                         the_view->perspective_near);

    glUniform4fv(light_direction_loc, 1,
                 glm::value_ptr( view_transform *  a_light.light_direction_position));


    static auto last_time = 0.0;
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

//        glm::vec4 ambient_product = *a_light.ambient_light.as_vec4()
//                * *obj->surface_material.ambient_color.as_vec4();
//        glm::vec4 diffuse_product = *a_light.diffuse_light.as_vec4()
//                                    * *obj->surface_material.diffuse_color.as_vec4();
//        glm::vec4 specular_product = *a_light.specular_light.as_vec4()
//                                    * *obj->surface_material.specular_color.as_vec4();

        glUniform4fv(ambient_light_loc, 1, a_light.ambient_light.as_float());
        glUniform4fv(diffuse_light_loc, 1, a_light.diffuse_light.as_float());
        glUniform4fv(specular_light_loc, 1, a_light.specular_light.as_float());
        glUniform4fv(ambient_color_loc, 1, obj->surface_material.ambient_color.as_float());
        glUniform4fv(diffuse_color_loc, 1,  obj->surface_material.diffuse_color.as_float());
        glUniform4fv(specular_color_loc, 1, obj->surface_material.specular_color.as_float());
        glUniform1f(specular_shininess_loc, obj->surface_material.shininess);
        glUniform1f(specular_strength_loc, obj->surface_material.specular_strength);
        glUniform1i(sampler_loc, obj->texture_unit);

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
