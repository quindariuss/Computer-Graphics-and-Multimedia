


#include <GLM/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "cs4722/x11.h"
#include "cs4722/shape.h"
#include "cs4722/load_shaders.h"


static int  number_of_vertices;

void
init(void)
{

    GLuint program = cs4722::load_shaders("vertex_shader05.glsl","fragment_shader05.glsl");
    glUseProgram(program);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


    // cs4722::shape* shape = new cs4722::sphere(5, 10);
//    cs4722::shape* shape = new cs4722::sphere(5, 22);
    // cs4722::shape* shape = new cs4722::sphere(50, 220);
     cs4722::shape* shape = new cs4722::torus(.1, 15, 30);
    // cs4722::shape* shape = new cs4722::cylinder(0, 20);
    // cs4722::shape* shape = new cs4722::block();
    // cs4722::shape* shape = new cs4722::torus_points(.5, 10, 20);

	std::cout << "number of vertices " << shape->get_size() << std::endl;


	
    number_of_vertices = shape->get_size();

    std::vector<glm::vec4>* positionsV = shape->positions();
    glm::vec4* positions = positionsV->data();
   

    std::vector<cs4722::color>* colorsV = shape->colors();
    cs4722::color* colors = colorsV->data();
  

    

    const auto number_of_buffers = 2;
    GLuint  buffers[number_of_buffers];
    const auto b_position = glGetAttribLocation(program, "bPosition");
    const auto b_color = glGetAttribLocation(program, "bColor");
    glGenBuffers(number_of_buffers, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, number_of_vertices * 4 * 4, positions, 0);
    glVertexAttribPointer(b_position, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(b_position);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferStorage(GL_ARRAY_BUFFER, number_of_vertices * 4 * 1, colors, 0);
    glVertexAttribPointer(b_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, nullptr);
    glEnableVertexAttribArray(b_color);

    delete positionsV;
    delete colorsV;
}




//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
    glClear(GL_DEPTH_BUFFER_BIT);

    
//    glDrawArrays(GL_POINTS, 0, number_of_vertices);
//    glDrawArrays(GL_LINES, 0, number_of_vertices);
//    glDrawArrays(GL_LINE_STRIP, 0, number_of_vertices);
    //glDrawArrays(GL_LINE_LOOP, 0, NumVertices);
    glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, number_of_vertices);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, number_of_vertices);
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


    GLFWwindow* window = glfwCreateWindow(w_width, w_height, "Many Points", NULL, NULL);
    glfwSetWindowPos(window, w_x, w_y);

    glfwMakeContextCurrent(window);
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
