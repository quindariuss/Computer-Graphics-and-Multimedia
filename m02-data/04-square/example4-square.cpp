


#include <GLM/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "cs4722/x11.h"
#include "cs4722/load_shaders.h"

const auto  number_of_vertices = 6;


void
init1(void)
{

    const auto program = cs4722::load_shaders("vertex_shader04.glsl","fragment_shader04.glsl");
    glUseProgram(program);

    glEnable(GL_PROGRAM_POINT_SIZE);


    GLfloat a = .5;
    glm::vec4 ul = glm::vec4(-a, a, 0, 1);
    glm::vec4 ll = glm::vec4(-a, -a, 0, 1);
    glm::vec4 lr = glm::vec4(a, -a, 0, 1);
    glm::vec4 ur = glm::vec4(a, a, 0, 1);

    glm::vec4 vertices[number_of_vertices] = { ll, ur, ul, ur, ll, lr };



	// constant color
    const cs4722::color colors1[number_of_vertices] = { cs4722::x11::orange,
      cs4722::x11::orange,cs4722::x11::orange,cs4722::x11::orange,cs4722::x11::orange,
      cs4722::x11::orange,
    };

	// six colors, two corners get competing colors
    const cs4722::color colors2[number_of_vertices] = { cs4722::x11::white,
      cs4722::x11::blue, cs4722::x11::black, cs4722::x11::yellow,
      cs4722::x11::gray, cs4722::x11::orange,
    };
    // { ll, ur, ul, ur, ll, lr };


	// All corners have consistent colors, but diagonal stripe is still evident
    const cs4722::color colors3[number_of_vertices] = { cs4722::x11::white,
     cs4722::x11::blue, cs4722::x11::blue, cs4722::x11::blue,
     cs4722::x11::white, cs4722::x11::orange,
   };
    // { ll, ur, ul, ur, ll, lr };

	
    const auto number_of_buffers = 2;
	
    GLuint  buffers[number_of_buffers];
    const auto b_position = glGetAttribLocation(program, "bPosition");
    const auto b_color = glGetAttribLocation(program, "bColor");
    glGenBuffers(number_of_buffers, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, number_of_vertices*4*4, vertices, 0);
    glVertexAttribPointer(b_position, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(b_position);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferStorage(GL_ARRAY_BUFFER, number_of_vertices*4*1, colors3, 0);
    glVertexAttribPointer(b_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
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

   
//    glDrawArrays(GL_POINTS, 0, number_of_vertices);
//    glDrawArrays(GL_LINES, 0, number_of_vertices);
//    glDrawArrays(GL_LINE_STRIP, 0, number_of_vertices);
//    glDrawArrays(GL_LINE_LOOP, 0, number_of_vertices);
    glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, number_of_vertices);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, number_of_vertices);
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


    GLFWwindow* window = glfwCreateWindow(w_width, w_height, "Square", NULL, NULL);
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
