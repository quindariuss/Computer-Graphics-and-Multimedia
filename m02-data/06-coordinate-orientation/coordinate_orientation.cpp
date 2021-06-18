


#define _USE_MATH_DEFINES
// #include <cmath>
#include <iostream>

#include <GLM/glm.hpp>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include "cs4722/x11.h"
#include "cs4722/load_shaders.h"



const GLuint  number_of_vertices = 6;

void
init1(void)
{
    GLuint program = cs4722::load_shaders("vertex_shader06.glsl","fragment_shader06.glsl");
    glUseProgram(program);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

  


    // blue in front at positive x
    // yellow in back at positive y
    // blue drawn first
   //  float  vertices[NumVertices][4] = {
   //     {.9, 0, .5, 1},
   // 	{-.9, 0, .5, 1},
   // 	{0, -.2, .5, 1},
   // 	{0, .9, -.5, 1},
   // 	{0, -.9, -.5, 1},
   // 	{.2, 0, -.5, 1}
   // };

    // blue negative z at positive y
    // yellow positive z at positive x
    // blue drawn first
    float  vertices[number_of_vertices][4] = {
   {0, .9, -.5, 1},
   {0, -.9, -.5, 1},
   {.2, 0, -.5, 1},
      {.9, 0, .5, 1},
   {-.9, 0, .5, 1},
   {0, -.2, .5, 1},
    };


    std::cout << "sizeof vertices " << sizeof(vertices) << std::endl;

    const float* colorList[number_of_vertices] = {  cs4722::x11::blue.as_float(), cs4722::x11::gray75.as_float(),
        cs4722::x11::gray25.as_float(), cs4722::x11::yellow.as_float(), cs4722::x11::gray75.as_float(),
        cs4722::x11::gray25.as_float(),
    };
    float colors[number_of_vertices][4];
    for (int i = 0; i < number_of_vertices; i++) {
        for (int j = 0; j < 4; j++) {
            colors[i][j] = colorList[i][j];
        }
    }
   

    const auto number_of_buffers = 2;
    GLuint  buffers[number_of_buffers];
    const auto b_position = glGetAttribLocation(program, "bPosition");
    const auto b_color = glGetAttribLocation(program, "bColor");
    glGenBuffers(number_of_buffers, buffers);


    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
    glVertexAttribPointer(b_position, 4, GL_FLOAT,
        GL_FALSE, 0, 0);
    glEnableVertexAttribArray(b_position);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(colors), colors, 0);
    glVertexAttribPointer(b_color, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(b_color);


}

//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
    glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
    glClear(GL_DEPTH_BUFFER_BIT);
	
   
    glDrawArrays(GL_POINTS, 0, number_of_vertices);
    //glDrawArrays(GL_LINES, 0, NumVertices);
    //glDrawArrays(GL_LINE_STRIP, 0, NumVertices);
    //glDrawArrays(GL_LINE_LOOP, 0, NumVertices);
    glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, NumVertices);
    // glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);
}

int
main(int argc, char** argv)
{
    glfwInit();

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    int xpos, ypos, width, height;
    glfwGetMonitorWorkarea(primary, &xpos, &ypos, &width, &height);
    //std::cout << xpos << " " << ypos << " " << width << " " << height << std::endl;
    int size = glm::min(width, height);
    float ratio = .9f;
    int w_width = int(ratio * size);
    int w_height = w_width;
    int w_x = int(size * (1 - ratio) / 2);
    int w_y = w_x;


    GLFWwindow* window = glfwCreateWindow(w_width, w_height, "Coordinate Orientation", NULL, NULL);
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
