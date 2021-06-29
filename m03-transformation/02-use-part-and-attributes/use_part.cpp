


#include "GLM/gtc/type_ptr.hpp"

#include <algorithm>


#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "cs4722/x11.h"
#include "cs4722/part.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"

static GLuint program;
static GLuint u_transform;

static cs4722::part part;

void init(void)
{

    program = cs4722::load_shaders("vertex_shader-m04.glsl","fragment_shader-m04.glsl");
    glUseProgram(program);

    u_transform = glGetUniformLocation(program, "transform");

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


//    auto* vBuf = new std::vector<GLfloat>();
//    auto* cBuf = new std::vector<GLubyte>();

	
    // create a shape
    //cs4722::shape *b =  new cs4722::cylinder(.75, 20);
    cs4722::shape* b = new cs4722::sphere(15,50);
    // cs4722::shape* b = new cs4722::block();
//    obj = new cs4722::object();
    part.the_shape = b;
    // obj->translate = (glm::vec3(.5, -.5, 0));
    part.world_transform.rotation_axis = (glm::vec3(1, 1, 1));
    part.world_transform.rotation_angle = (M_PI / 4);
    part.world_transform.rotation_center = (glm::vec3(0, 0, .7));
    part.world_transform.scale = (glm::vec3(.5f, .7f, .5f));
    part.the_shape->buffer_size = part.the_shape->get_size();
    part.the_shape->buffer_start = 0;


    auto number_of_vertices = b->get_size();

    auto* positions = part.the_shape->positions();
    auto* colors = part.the_shape->colors();

    const int number_of_buffers = 2;
    GLuint  buffers[number_of_buffers];
    glCreateBuffers(number_of_buffers, buffers);
    const auto b_position = glGetAttribLocation(program, "bPosition");
    const auto b_color = glGetAttribLocation(program, "bColor");

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, 4 * 4 * number_of_vertices, positions->data(), 0);
    glVertexAttribPointer(b_position, 4, GL_FLOAT,
        GL_FALSE, 0, 0);
    glEnableVertexAttribArray(b_position);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferStorage(GL_ARRAY_BUFFER, 1 * 4 * number_of_vertices, colors->data(), 0);
    glVertexAttribPointer(b_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(b_color);

    delete positions;
    delete colors;
    

}

//----------------------------------------------------------------------------
//
// display
//

void
display()
{
 
 
    glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
    glClear(GL_DEPTH_BUFFER_BIT);


    auto tr = part.world_transform.matrix();

    glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(tr));

    glDrawArrays(GL_TRIANGLES, part.the_shape->buffer_start, part.the_shape->buffer_size);
   
}

int
main(int argc, char** argv)
{
    glfwInit();

    auto *window = cs4722::setup_window("Use Part Class", .7);

    gladLoadGL(glfwGetProcAddress);

    init();

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
