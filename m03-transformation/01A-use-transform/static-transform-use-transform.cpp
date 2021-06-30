


// #include <glm.h>
#include "GLM/glm.hpp"
#include "GLM/ext.hpp"


#include <algorithm>

#include <glad/gl.h>
#include <GLFW/glfw3.h>



#include <cs4722/transform.h>
#include "cs4722/x11.h"
#include "cs4722/shape.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"


static GLuint  number_of_vertices;
static GLuint program;
static GLuint u_transform;

void
init(void)
{


    program = cs4722::load_shaders("vertex_shader-m04.glsl" ,"fragment_shader-m04.glsl" );
    glUseProgram(program);

    u_transform = glGetUniformLocation(program, "transform");


    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


//    auto* vBuf = new std::vector<GLfloat>();
//    auto* cBuf = new std::vector<GLubyte>();

	
    // create a shape
    // cs4722::shape *b =  new cs4722::cylinder(.05, 20);
    // cs4722::shape* b = new cs4722::cylinder();
    cs4722::shape* b = new cs4722::sphere(15,50);
    // cs4722::shape* b = new cs4722::sphere(4, 5);
    // cs4722::shape* b = new cs4722::block();

    
    number_of_vertices = b->get_size();

	auto* positions = b->positions();
    auto* colors = b->colors();

    // enum Buffer_IDs { bPosition, bColor, NumBuffers };
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
display(void)
{


    auto* tr = new cs4722::transform();
    tr->translate = glm::vec3(-.5f, -.5f, 0.0f);
    tr->rotation_angle = -M_PI / 4;
    tr->rotation_axis = glm::vec3(0,0,1);
    tr->scale = glm::vec3(.2f, .5f, .5f);
    auto tr_matrix = tr->matrix();


    glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(tr_matrix));
    
    glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);
    
}

int
main(int argc, char** argv)
{
    glfwInit();


    auto * window = cs4722::setup_window("Static Transorm Use Transform", .7);

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
