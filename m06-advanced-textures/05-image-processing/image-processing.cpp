

#include "sharing.h"

#include "cs4722/window.h"
#include "cs4722/callbacks.h"

/*
 * This example is much like the render to texture example.
 * There is a scene created from a few parts that is rendered both to a texture.
 * There is a rectangle that is rendered using the texture created in the rendering operation.
 * There are some important differences:
 *
 *      * The parts in the first sub-scene are not rendered directly to the window framebuffer
 *      * Instead, the 'view in view' rectangle covers the entire window.
 *      * The camera is not reversed when rendering the parts to the framebuffer
 *          * This makes navigation work as expected
 *      * The fragment shader for rendering the view-in-view rectangle to the window framebuffer
 *          processes the texture fragments in various ways
 */

int
main(int argc, char** argv)
{
    glfwInit();

    auto *window = cs4722::setup_window("Image Processing", .9);


    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();


    auto *view = new cs4722::view();
//    view->enable_logging = false;
   view->set_flup(glm::vec3(0.313269,0.342897,-0.885598),
                   glm::vec3(-0.942755,0,-0.333488),
                   glm::vec3(-0.114352,0.939372,0.323268),
                   glm::vec3(-0.323962,-0.506261,0.967844)
    );

//    view->perspective_fovy = (.9 * M_PI);

    parts_setup(view);
    view_in_view_setup(view);

    glfwSetWindowUserPointer(window, view);

    cs4722::setup_user_callbacks(window);
	
    while (!glfwWindowShouldClose(window))
    {
        parts_setup_for_fb();
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);
        // parts only in the framebuffer this time
        parts_display();

        /*
         * parts_setup_for_window is being used here because it sets up the window framebuffer
         * properly.
         * We will not be rendering the parts directly to the window.
         */
        parts_setup_for_window(window);
        // we will actually not see the olive drab since the view-in-view rectangle will
        //  cover the entire window
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::olive_drab.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);
        view_in_view_display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
