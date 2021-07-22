
/*
 * Make the setup and display functions of the two parts of the scene available
 * to call.
 */
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

    // create a view here to be shared by all parts of the scene
    auto *view = new cs4722::view();

    skybox_setup(view);
    parts_setup(view);

    glfwSetWindowUserPointer(window, view);
    cs4722::setup_user_callbacks(window);

//    glfwSetKeyCallback(window, cs4722::general_key_callback);
//    glfwSetCursorPosCallback(window, cs4722::move_callback);
//    glfwSetWindowSizeCallback(window, cs4722::window_size_callback);
	
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);
        skybox_display();
        parts_display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
