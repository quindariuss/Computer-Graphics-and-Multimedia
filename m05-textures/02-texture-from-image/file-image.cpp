


//#include <GLM/glm.hpp>
#include <GLM/vec2.hpp>


//#define _USE_MATH_DEFINES
//#include <cmath>
#include <iostream>
#include <vector>

#include <glad/gl.h>

#include <GLFW/glfw3.h>


#include "cs4722/x11.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"
#include "cs4722/callbacks.h"

#include "STB//stb_image.h"



const GLuint  NumVertices = 6;
GLuint program;

void init(void)
{
    program = cs4722::load_shaders("vertex_shader01.glsl","fragment_shader01.glsl");
    glUseProgram(program);


    // generate the vertex data

    GLfloat a = .9f;
    GLfloat b = .9f;
    glm::vec4 ul = glm::vec4(-b, a, 0, 1);
    glm::vec4 ll = glm::vec4(-b, -b, 0, 1);
    glm::vec4 lr = glm::vec4(a, -b, 0, 1);
    glm::vec4 ur = glm::vec4(a, a, 0, 1);

    glm::vec4 position_list[NumVertices] = { ll, ur, ul, ur, ll, lr };
    

    // generate the texture coordinate data

    auto upper_texture = 1.0f;
    auto lower_texture = 0.0f;
    auto llt = glm::vec2(lower_texture, upper_texture);
    auto ult = glm::vec2(lower_texture, lower_texture);
    auto urt = glm::vec2(upper_texture, lower_texture);
    auto lrt = glm::vec2(upper_texture, upper_texture);
    glm::vec2 texture_coordinate_list[NumVertices] = { llt, urt, ult, urt, llt, lrt };


    
    const auto number_of_buffers = 2;
    GLuint buffers[number_of_buffers];

    glGenBuffers(number_of_buffers, buffers);
    auto bPosition = glGetAttribLocation(program, "bPosition");
    auto bTextureCoord = glGetAttribLocation(program, "bTextureCoord");
    auto bColor = glGetAttribLocation(program, "bColor");

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, 4*4*NumVertices, position_list, 0);
    glVertexAttribPointer(bPosition, 4, GL_FLOAT,
        GL_FALSE, 0, 0);
    glEnableVertexAttribArray(bPosition);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferStorage(GL_ARRAY_BUFFER, 4 * 2 * NumVertices, 
        texture_coordinate_list, 0);
    glVertexAttribPointer(bTextureCoord, 2, GL_FLOAT,
        GL_FALSE, 0, 0);
    glEnableVertexAttribArray(bTextureCoord);

    
}

void init_texture() {

    // get the image data from a file
    int texture_width, texture_height, n;
    // program runs in directory cmake-build-debug
    // provide a relative path to the media file used for the image
    unsigned char *texture_data = stbi_load("../media/tulips-bed-256x256.png",
        &texture_width, &texture_height, &n, 0);



	GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    auto number_of_levels = 1;
    auto internal_format = GL_RGBA8;
    auto external_format = GL_RGB;

    glActiveTexture(GL_TEXTURE0);
    glTexStorage2D(GL_TEXTURE_2D, number_of_levels, internal_format,
        texture_width, texture_height);
//    glBindTextureUnit(0, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture_width, texture_height,
        external_format, GL_UNSIGNED_BYTE, texture_data);
  

    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, cs4722::x11::aquamarine.as_float());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    auto mag_filter = GL_NEAREST;
//    auto mag_filter = GL_LINEAR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
     auto wrap_type = GL_CLAMP_TO_EDGE;
//    auto wrap_type = GL_MIRRORED_REPEAT;
    // auto wrap_type = GL_REPEAT;
    // auto wrap_type = GL_CLAMP_TO_BORDER;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_type);
  
    const auto sampler_loc = glGetUniformLocation(program, "sampler");
    glUniform1i(sampler_loc, 0);

}


void
display(void)
{
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

int
main(int argc, char** argv)
{
    glfwInit();
    auto *window = cs4722::setup_window("Texture From Image", .9);
    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();
    init();
    init_texture();

    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
