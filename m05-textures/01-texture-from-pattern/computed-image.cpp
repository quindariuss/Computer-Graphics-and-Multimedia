


/*
 * Texture coordinates are two dimensional, so we include vec2.
 */
#include <GLM/vec2.hpp>

#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include "cs4722/x11.h"
#include "cs4722/window.h"
#include "cs4722/load_shaders.h"
#include "cs4722/callbacks.h"


const GLuint  NumVertices = 6;
GLuint program;

void init(void)
{

    /*
     * Check the fragment shader code for comments.
     */
    program = cs4722::load_shaders("vertex_shader01.glsl","fragment_shader01.glsl");
    glUseProgram(program);


    /*
     * We are just using a single square to display textures in the first two examples.
     * This will let us see how texture coordinates actually match up to the vertices.
     */

    // generate the vertex position data
    // simple square with corners .7 of the way to the window corners
    GLfloat a = .7f;
    GLfloat b = .7f;
    glm::vec4 ul = glm::vec4(-b, a, 0, 1);
    glm::vec4 ll = glm::vec4(-b, -b, 0, 1);
    glm::vec4 lr = glm::vec4(a, -b, 0, 1);
    glm::vec4 ur = glm::vec4(a, a, 0, 1);

    glm::vec4 position_list[NumVertices] = { ll, ur, ul, ur, ll, lr };


    // generate the texture coordinate data
    // These are the corners of the unit square with one vertex at the origin.
	auto upper_texture = 1.0f;
	auto lower_texture = 0.0f;
	auto ult = glm::vec2(lower_texture, upper_texture);
	auto llt = glm::vec2(lower_texture, lower_texture);
	auto lrt = glm::vec2(upper_texture, lower_texture);
	auto urt = glm::vec2(upper_texture, upper_texture);
	/*
	 * The next list associates texture coordinates with vertices.
	 * Changing the elements in the list will change how the texture is 'painted' onto the surface.
	 */
	glm::vec2 texture_coordinate_list[NumVertices] = { llt, urt, ult, urt, llt, lrt };



	/*
	 * Since we are not working with shapes, we have to set up the buffers manually.
	 */
    const auto number_of_buffers = 2;
    GLuint buffers[number_of_buffers];

    glGenBuffers(number_of_buffers, buffers);
    auto bPosition = glGetAttribLocation(program, "bPosition");
    auto bTextureCoord = glGetAttribLocation(program, "bTextureCoord");
   
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, 4 * 4 * NumVertices, position_list, 0);
    glVertexAttribPointer(bPosition, 4, GL_FLOAT,
        GL_FALSE, 0, 0);
    glEnableVertexAttribArray(bPosition);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    // Texture coordinates are 2D, so two floats per vertex
    glBufferStorage(GL_ARRAY_BUFFER, 4 * 2 * NumVertices,
        texture_coordinate_list, 0);
    glVertexAttribPointer(bTextureCoord, 2, GL_FLOAT,
        GL_FALSE, 0, 0);
    glEnableVertexAttribArray(bTextureCoord);

   

}


void init_texture() {

    /*
     * Using a texture will be a two step process for us:
     *  1. Creating an image in memory
     *  2. Creating an OpenGL texture object and other supporting objects while filling with the
     *      image data
     */


    /*
     * This image will be procedurally generated.
     * First we specify the width and height in pixels.
     */
    auto texture_width = 64;
    auto texture_height = 64;

    /*
     * The image data will be stored in a list.
     * Each pixel will take four bytes each with values ranging from 0 to 255.
     * The image is stored by rows, starting at the bottom row at the left.
     *
     */
    auto texture_data = new std::vector<GLubyte>();
    // create data
    for (int r = 0; r < texture_height; r++) {
        for (int c = 0; c < texture_width; c++) {
            /*
             * Each pixel is  blend of yellow and blue
             * The highest row is bright yellow, the lowest has no yellow contribution
             * The rightmost columns is bright blue, the leftmost has no blue contribution
             */
            texture_data->push_back(r * 255 / texture_height);
            texture_data->push_back(r * 255 / texture_width);
            texture_data->push_back(c * 255 / texture_height);
            texture_data->push_back(255); // alpha value signifies opaque
        }
    }

    /*
     * The image is now stored in adjacent bytes in memory inside the vector structure.
     * That data will be used to fill the OpenGL texture.
     */

    // initialize texture and sampler


    glActiveTexture(GL_TEXTURE2);
    /*
     * Creating a texture is similar to creating a buffer.
     * Set aside an int variable for a texture object identifier.
     * Allocate a texture and store the value in the int.
     */
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // We discussed mipmaps but will not be using them in this example, so only one level of images
    auto number_of_levels = 1;
    // the image created above uses RGBA components, each stored in an 8 bit byte
    auto internal_format = GL_RGBA8;
    // The image will be stored internally using rgba, no specification of how each component
    //      is stored
    auto external_format = GL_RGBA;


    // changes needed here

    // describe the texture: number of levels, internal format, width and height
    // allows the system to allocate the right amount of memory for the texture data
    glTexStorage2D(GL_TEXTURE_2D, number_of_levels, internal_format, texture_width, texture_height);
    /*
     * move the data into the texture.
     * Parameter description from the documentation, describing parameters in order:

    texture: Specifies the texture object name for glTextureSubImage2D. The effective target of texture must be one of the valid target values above. level

    level: Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
    xoffset: Specifies a texel offset in the x direction within the texture array.
    yoffset: Specifies a texel offset in the y direction within the texture array.

    width: Specifies the width of the texture subimage.
    height: Specifies the height of the texture subimage.

    format: Specifies the external format of the pixel data.

    type: Specifies the data type of the pixel data.

    pixels: Specifies a pointer to the image data in memory.

     */
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                        texture_width, texture_height,
                        external_format, GL_UNSIGNED_BYTE, texture_data->data());
    /*
     * Textures are accessed through texture units.
     * Texture units are numbered.
     * We're using texture unit number 2, just to do something non-default.
     */
//    glBindTextureUnit(2, texture);


    /*
     * Now set some parameters for how textures will be processed.
     * We don't have programmatic control but can set numerous parameters that affect the processing.
     */
    /*
     * Under some conditions a border color will be used.
     * This function sets the color.
     * The first parameter is the texture id
     * The second parameter specifies the texture parameter using a symbolic constant
     * The third parameter provides the value
     *
     * The characters 'fv' at the end of the function name indicate that the parameter value expected
     * is an array of float.
     */
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, cs4722::x11::aquamarine.as_float());
    //  The min filter is not operational in this example since the texture is much smaller than
    //      the area to cover, so there is no point in setting the min filter.
    // glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The mag filter can have two values for the texture we are configuring: nearest and linear
    // uncomment exactly on of the next two lines to choose which max filter to use
    auto mag_filter = GL_NEAREST;
    // auto mag_filter = GL_LINEAR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    /*
     * What happens when the texture coordinates are out of the range from 0 to 1?
     * Various possibilities are represented by the different symbolic constants below.
     * Uncomment exactly one of the next four lines.
     */
    auto wrap_type = GL_CLAMP_TO_EDGE;
    // auto wrap_type = GL_MIRRORED_REPEAT;
    // auto wrap_type = GL_REPEAT;
    // auto wrap_type = GL_CLAMP_TO_BORDER;

    // set the wrap to be the same in both coordinate directions.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_type);
    

    /*
     * There is a sampler variable in the fragment shader that will be used to access
     * texels from the texture.
     * The sampler variable is a uniform variable.
     * The next statement gets the location of the uniform variable.
     */
    auto sampler_loc = glGetUniformLocation(program, "sampler");
    // this next statement sets the sampler value to 2, the unit number we specified above
    glUniform1i(sampler_loc, 2);

}

/*
 * Alternative texture from the text.
 * We won't go into detail here, but make a few comments.
 */
void init_texture2() {

    GLuint tex;

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    // four levels of mipmaps
    glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, 8, 8);

    static const unsigned char texture_data[] =
    {
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
    };

    /*
     * The input data only provides the red channel: GL_RED
     * There is one byte per pixel
     */
    glTexSubImage2D(GL_TEXTURE_2D,
        0,
        0, 0,
        8, 8,
        GL_RED, GL_UNSIGNED_BYTE,
        texture_data);

    /*
     * Swizzling creates alternate mappings from image data to texture data.
     * In this case the red component of the input (the only component in the image)
     * is mapped to red and green and blue.
     * This makes a gray scale image.
     *
     * GL_ONE indicates that the alpha channel in the texture will be 1.0, opaque.
     */
    static const GLint swizzles[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzles);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // mipmaps are generated
    glGenerateMipmap(GL_TEXTURE_2D);
}

//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
     glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

int
main(int argc, char** argv)
{
    glfwInit();

    auto *window = cs4722::setup_window("Computed Texture", 0.9);

    gladLoadGL(glfwGetProcAddress);

    init();
    cs4722::setup_debug_callbacks();
    init_texture();

    /*
     * Display characteristics of the graphics card in supporting textures

     Here is the output on my laptop with Intel graphics selected:
        OpenGL version 4.6.0 - Build 26.20.100.7985
        OpenGL renderer Intel(R) UHD Graphics 630
        max texture units 32
        max texture size 2048

    Here is the output with the graphics card selected:
        OpenGL version 4.6.0 NVIDIA 452.41
        OpenGL renderer GeForce GTX 1050 Ti with Max-Q Design/PCIe/SSE2
        max texture units 32
        max texture size 16384



     */
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL renderer " << glGetString(GL_RENDERER) << std::endl;
    GLint max_texture_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
    std::cout << "max texture units " << max_texture_units << std::endl;
    GLint max_texture_size;
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &max_texture_size);
    std::cout << "max texture size " << max_texture_size << std::endl;
	

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
