



#include "GLM/gtc/type_ptr.hpp"

#include <list>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "cs4722/x11.h"
#include "cs4722/shape.h"
#include "cs4722/part.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"

static GLuint program;
static std::list<cs4722::part*> part_list;

static GLuint transform_loc;

void init(void)
{


    program = cs4722::load_shaders("vertex_shader-m04.glsl","fragment_shader-m04.glsl");
    glUseProgram(program);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    transform_loc = glGetUniformLocation(program, "transform");


    // create a shape
    //cs4722::shape *b =  new cs4722::cylinder(.75, 20);
    cs4722::shape* b = new cs4722::sphere(15,50);
    // cs4722::shape* b = new cs4722::block();
    auto* part = new cs4722::part();
    part->the_shape = (b);
    part->world_transform.translate = (glm::vec3(.5, -.5, 0));
    part->world_transform.rotation_axis = (glm::vec3(0, 1, 1));
    part->world_transform.rotation_angle = (M_PI / 3);
    part->world_transform.scale = (glm::vec3(.4f, .6f, .4f));
 
    part_list.push_back(part);

	
    cs4722::shape* b1 = new cs4722::block();
    auto* part1 = new cs4722::part();
    part1->the_shape = (b1);
    part1->world_transform.translate = (glm::vec3(-.5, -.5, 0));
    part1->world_transform.rotation_axis = (glm::vec3(1, 1, 0));
    part1->world_transform.rotation_angle = (M_PI / 4);
    part1->world_transform.scale = (glm::vec3(.4f, .6f, .4f));

    part_list.push_back(part1);


    auto* p_buf = new std::vector<glm::vec4>();
    auto* c_buf = new std::vector<cs4722::color>();
	
    for (auto current_part : part_list) {

        auto* current_shape = current_part->the_shape;
  
        current_shape->buffer_size = current_shape->get_size();
        current_shape->buffer_start = p_buf->size();

        auto* vertices = current_shape->positions();
        p_buf->insert(p_buf->end(), vertices->begin(), vertices->end());
        delete vertices;

        auto* colors = current_shape->colors();
        c_buf->insert(c_buf->end(), colors->begin(), colors->end());
        delete colors;

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
 
    //std::cout << "nm vertices " << NumVertices << std::endl;
    

    for (auto part : part_list) {
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(part->world_transform.matrix()));
        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
    }
}

int
main(int argc, char** argv)
{
    glfwInit();

    auto *window = cs4722::setup_window("Multiple Parts", .7);

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
