


//#include <GL3/gl3.h>
#include <glad/gl.h>

// #include <GL/glext.h>

#include <GLFW/glfw3.h>


#include <iostream>
#include <cs4722/load_shaders.h>


void
init(void)
{

    GLuint program = cs4722::load_shaders("vertex_shader05.glsl","fragment_shader05.glsl");
    glUseProgram(program);


    glEnable(GL_PROGRAM_POINT_SIZE);


}


void
display(void)
{
    static const float gray50[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, gray50);

    glDrawArrays(GL_POINTS, 0, 1);
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


int main(void)
{
    

    glfwSetErrorCallback(error_callback);

	
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    auto *window = 
        glfwCreateWindow(500, 500, "One Point", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);

     std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
     std::cout << "OpenGL renderer " << glGetString(GL_RENDERER) << std::endl;


    init();

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
