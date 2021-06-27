



#include "GLM/gtc/type_ptr.hpp"



#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include "cs4722/buffer_utilities.h"
#include "cs4722/load_shaders.h"
#include "cs4722/window.h"

static GLuint program;
static GLuint transform_loc;
static std::vector<cs4722::part*> part_list;

void init(void)
{
    program = cs4722::load_shaders("vertex_shader.glsl","fragment_shader.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);



    auto* centerCube = new cs4722::block();
    auto* torus = new cs4722::torus();
    auto* cylinderNorth = new cs4722::cylinder();
    auto* cylinderSouth = new cs4722::cylinder();
    auto* cylinderEast = new cs4722::cylinder();
    auto* cylinderWest = new cs4722::cylinder();

    auto z = 0;

    auto number = 5;
    auto d = 4.0f / (2 * number + 1);
    auto radius = d / 4;
    auto base = -1 + 3 * radius;

    for (auto x = 0; x < number; ++x) // number of horizontal rows
    {
        for (auto y = 0; y < number; ++y) // number of vertical rows
        {
            auto* object0 = new cs4722::part();
            object0->the_shape = centerCube;
            object0->world_transform.translate = glm::vec3(base + x * d, base + y * d, base + z * d);
            object0->world_transform.scale = glm::vec3(radius, radius, radius);
            object0->animation_transform.rotation_axis = glm::vec3(3 * x + 1, 3 * y + 1, 3 * z + 1);
            object0->animation_transform.rotation_center =
                    object0->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
            //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));

            auto* object1 = new cs4722::part_rotating();
            object1->the_shape = torus;
            object1->world_transform.translate = glm::vec3(base + x * d, base + y * d, base + z * d);
            object1->world_transform.scale = glm::vec3(radius, radius, radius);
            object1->animation_transform.rotation_axis = glm::vec3(3 * x + 1, 3 * y + 1, 3 * z + 1);
            object1->animation_transform.rotation_center =
                    object1->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
            //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));
            object1->rotation_rate = M_PI / 3;
            auto* object2 = new cs4722::part_rotating();
            object2->the_shape = cylinderNorth;
            object2->world_transform.translate = glm::vec3(base + x * d, base + y * d, base + z * d);
            object2->world_transform.scale = glm::vec3(radius, radius, radius);
            object2->animation_transform.rotation_axis = glm::vec3(3 * x + 1, 3 * y + 1, 3 * z + 1);
            object2->animation_transform.rotation_center =
                    object2->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
            //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));
            object2->rotation_rate = M_PI / 3;


            auto* object3 = new cs4722::part_rotating();
            object3->the_shape = cylinderEast;
            object3->world_transform.translate = glm::vec3(base + x * d, base + y * d, base + z * d);
            object3->world_transform.scale = glm::vec3(radius, radius, radius);
            object3->animation_transform.rotation_axis = glm::vec3(3 * x + 1, 3 * y + 1, 3 * z + 1);
            object3->animation_transform.rotation_center =
                    object3->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
            //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));


            auto* object4 = new cs4722::part_rotating();
            object4->the_shape = cylinderSouth;
            object4->world_transform.translate = glm::vec3(base + x * d, base + y * d, base + z * d);
            object4->world_transform.scale = glm::vec3(radius, radius, radius);
            object4->animation_transform.rotation_axis = glm::vec3(3 * x + 1, 3 * y + 1, 3 * z + 1);
            object4->animation_transform.rotation_center =
                    object1->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
            //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));


            auto* object5 = new cs4722::part_rotating();
            object5->the_shape = cylinderWest;
            object5->world_transform.translate = glm::vec3(base + x * d, base + y * d, base + z * d);
            object5->world_transform.scale = glm::vec3(radius, radius, radius);
            object5->animation_transform.rotation_axis = glm::vec3(3 * x + 1, 3 * y + 1, 3 * z + 1);
            object5->animation_transform.rotation_center =
                    object5->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
            //obj->set_rotation_rate(glm::linearRand(-M_PI/2, M_PI / 2));
            //adding parts to project
            part_list.push_back(object0);
//            part_list.push_backck(object1);
//            part_list.push_back(object2);
//            part_list.push_back(object3);
//            part_list.push_back(object4);
//            part_list.push_back(object5);

        }
    }

    cs4722::init_buffers(program, part_list, "bPosition", "bColor");


}



void display()
{

    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;

    // uncomment the following few lines to see the frame rate computed two different ways
//    static double  arate = 0.0;
//    auto x = (100 * arate + 1 / delta_time) / 101;
//    arate  = x;
//	printf("part count:  %d      rate:  %.3f    arate: %.3f\n", part_list.size(), 1/delta_time, arate);


    for (auto part : part_list) {
        part->animate(time, delta_time);
        auto model_matrix = part->animation_transform.matrix() * part->world_transform.matrix();
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
    	
        glDrawArrays(GL_TRIANGLES, part->the_shape->buffer_start, part->the_shape->buffer_size);
       

    }
}

int
main(int argc, char** argv)
{
    glfwInit();
    auto *window = cs4722::setup_window("Animation Many", .9);
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
