


#include "GLM/gtc/type_ptr.hpp"

#include <glad/gl.h>


#include "cs4722/part.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"


static std::vector<cs4722::part*> part_list;
static GLuint program;
static GLuint transform_loc;

void init(void)
{
    program = cs4722::load_shaders("vertex_shader-m04.glsl","fragment_shader-m04.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

	
    // create a shape
    //cs4722::shape *b =  new cs4722::cylinder(.75, 20);
    cs4722::shape* b = new cs4722::sphere(15,50);
    // cs4722::shape* b = new cs4722::block();
    auto* part = new cs4722::part_rotating();
    part->the_shape = b;
    part->world_transform.translate = glm::vec3(.5, -.5, 0);
    part->animation_transform.rotation_axis = glm::vec3(1, 1, 0);
    part->rotation_rate = M_PI / 3;
    part->world_transform.scale = glm::vec3(.4f, .6f, .4f);
    
    part_list.push_back(part);

	
    cs4722::shape* b1 = new cs4722::block();
    auto* part1 = new cs4722::part_rotating();
    part1->the_shape = b1;
    part1->world_transform.translate = glm::vec3(-.5, 0, 0);
    part1->animation_transform.rotation_axis = glm::vec3(1, 0, 1);
    part1->rotation_rate = M_PI / 3;
//    obj1->animation_transform.rotation_center = glm::vec3(0, .3f, 0);
    part1->world_transform.scale = glm::vec3(.2f, .6f, .2f);

    part_list.push_back(part1);

    cs4722::init_buffers(program, part_list, "bPosition", "bColor");

}

//----------------------------------------------------------------------------
//
// display
//


void
display()
{
 
    //std::cout << "nm vertices " << NumVertices << std::endl;

    glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
    glClear(GL_DEPTH_BUFFER_BIT);

    static auto last_time = 0.0;
//    printf("last time %.5f\n", last_time);
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;

    for (auto part : part_list) {
        part->animate(time, delta_time);
        auto model_matrix = part->animation_transform.matrix()
                            * part->world_transform.matrix();
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
    }
}

int
main(int argc, char** argv)
{
    glfwInit();
    auto *window = cs4722::setup_window("Animation", .9);

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
