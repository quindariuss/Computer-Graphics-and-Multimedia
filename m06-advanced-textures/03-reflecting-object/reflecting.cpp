

#include "sharing.h"

#include "cs4722/window.h"
#include "cs4722/callbacks.h"



int
main(int argc, char** argv)
{
    glfwInit();

    auto *window = cs4722::setup_window("Skybox", .9);


    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();


    auto *view = new cs4722::view();
//    view->enable_logging = false;
    view->set_flup(
    glm::vec3(0.266519,-0.0399901,-0.963003), glm::vec3(-0.963772,0,-0.266732),   glm::vec3(0.010666,0.999203,-0.0385406),  glm::vec3(0.229326,4.80626,1.7422)
    );
    auto cube_texture_unit = 77;

    skybox_setup(view);///, cube_texture_unit);
    parts_setup(view);
    reflecting_setup(view, cube_texture_unit);

    glfwSetWindowUserPointer(window, view);

    cs4722::setup_user_callbacks(window);
	
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);
        skybox_display();
        parts_display();
        reflecting_display();
//        printf("return from obj2 display\n");

        glfwSwapBuffers(window);
//        printf("swapped buffers\n");

        glfwPollEvents();
//        printf("polled events\n");
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
