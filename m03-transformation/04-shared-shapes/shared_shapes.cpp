



#include "GLM/gtc/type_ptr.hpp"

#include <glad/gl.h>

#include "cs4722/part.h"
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




    auto* p_buf = new std::vector<glm::vec4>();
    auto* c_buf = new std::vector<cs4722::color>();

    for (auto current_part : part_list) {

        auto* current_shape = current_part->the_shape;

        if (current_shape->buffer_size == 0) {  // test: skip shape if already processed
            current_shape->buffer_size = current_shape->get_size();
            current_shape->buffer_start = p_buf->size();

            auto* vertices = current_shape->positions();
            p_buf->insert(p_buf->end(), vertices->begin(), vertices->end());
            delete vertices;

            auto* colors = current_shape->colors();
            c_buf->insert(c_buf->end(), colors->begin(), colors->end());
            delete colors;
        }
    }


    const int number_of_buffers = 2;
    GLuint  buffers[number_of_buffers];
    glCreateBuffers(number_of_buffers, buffers);
    const auto b_position = glGetAttribLocation(program, "bPosition");
    const auto b_color = glGetAttribLocation(program, "bColor");

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, 4 * 4 * p_buf->size(), p_buf->data(), 0);
    glVertexAttribPointer(b_position, 4, GL_FLOAT,
        GL_FALSE, 0, 0);
    glEnableVertexAttribArray(b_position);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferStorage(GL_ARRAY_BUFFER, 1 * 4 * c_buf->size(), c_buf->data(), 0);
    glVertexAttribPointer(b_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(b_color);


    std::cout << "size vBuf " << p_buf->size() << std::endl;
	// 2673000  no sharing number = 15
	//     792  sharing number = 15
	
    delete p_buf;
    delete c_buf;

   

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

    auto *window = cs4722::setup_window("Shared Shapes", .9);

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
