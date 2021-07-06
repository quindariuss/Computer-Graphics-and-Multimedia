



#include "GLM/gtc/type_ptr.hpp"

#include <glad/gl.h>


#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"


static GLuint program;
static std::vector<cs4722::part*> part_list;
static GLuint transform_loc;

void init(void)
{

    program = cs4722::load_shaders("vertex_shader-m04.glsl","fragment_shader-m04.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");


    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);



	auto *sphere = new cs4722::sphere();

    auto number = 15 ;
    auto d = 4.0f / (2 * number + 1);
    auto radius = d / 4;
    auto base = -1 +  3 * radius;

	for(auto x = 0; x < number; ++x)
	{
        for (auto y = 0; y < number; ++y)
        {
            for (auto z = 0; z < number; ++z)
            {
                auto* part = new cs4722::part();
                part->the_shape = sphere;
                part->world_transform.translate = glm::vec3(base + x * d, base + y * d, base + z * d);
                part->world_transform.scale = glm::vec3(radius, radius, radius);
                part_list.push_back(part);
            }
        }
	}

    cs4722::init_buffers(program, part_list, "bPosition", "bColor");

   

}

//----------------------------------------------------------------------------
//
// display
//

void
display()
{

    for (auto part : part_list) {

        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(part->world_transform.matrix()));

        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
    }
}

int
main(int argc, char** argv)
{
    glfwInit();
    auto *window = cs4722::setup_window("Shared Shapes, Buffer Utility", .7);
    gladLoadGL(glfwGetProcAddress);

    init();

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
