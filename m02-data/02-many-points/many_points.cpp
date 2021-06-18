



#include <iostream>

#include <glad/gl.h>
#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>

#include "cs4722/load_shaders.h"




const auto  number_of_vertices = 7;

void
init1(void)
{
    auto program = cs4722::load_shaders("vertex_shader02.glsl", "fragment_shader02.glsl");
    glUseProgram(program);

    glEnable(GL_PROGRAM_POINT_SIZE);

    const auto delta = 2 * M_PI / number_of_vertices;
    const auto radius = .8f;
    glm::vec4 positions[number_of_vertices];
    for (auto i = 0; i < number_of_vertices; i++) 
    {
        auto angle = i * delta;
        positions[i] = glm::vec4(static_cast<float>(radius * cos(angle)), 
            static_cast<float>(radius * sin(angle)), 
            0.0, 
            1.0);
    }
	

    const auto number_of_buffers = 1;
    GLuint  buffers[number_of_buffers];
    glGenBuffers(number_of_buffers, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, number_of_vertices*4*4, positions, 0);
    const auto b_position = glGetAttribLocation(program, "vPosition");
    glVertexAttribPointer(b_position, 4, GL_FLOAT,
        GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(b_position);
}

//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
    static const float black[] = { 0.2f, 0.2f, 0.2f, 0.2f };

    glClearBufferfv(GL_COLOR, 0, black);

   
    glDrawArrays(GL_POINTS, 0, number_of_vertices);
    // glDrawArrays(GL_LINES, 0, number_of_vertices);
    glDrawArrays(GL_LINE_STRIP, 0, number_of_vertices);
    // glDrawArrays(GL_LINE_LOOP, 0, number_of_vertices);
    // glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, number_of_vertices);
    // glDrawArrays(GL_TRIANGLE_FAN, 0, number_of_vertices);

}


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int
main(int argc, char** argv)
{

    glfwSetErrorCallback(error_callback);
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    auto* primary = glfwGetPrimaryMonitor();
    int xpos, ypos, width, height;
    glfwGetMonitorWorkarea(primary, &xpos, &ypos, &width, &height);
    std::cout << xpos << " " << ypos << " " << width << " " << height << std::endl;
    const auto size = glm::min(width, height);
    const auto ratio = .9f;
    const auto w_width = static_cast<int>(ratio * size);
    const auto w_height = w_width;
    const auto w_x = static_cast<int>(size * (1 - ratio) / 2);
    const auto w_y = w_x;


    auto* window = glfwCreateWindow(w_width, w_height, "Many Points", NULL, NULL);
    glfwSetWindowPos(window, w_x, w_y);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    init1();

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
