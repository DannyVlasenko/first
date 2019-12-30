#include "render_loop.h"
#include "glfw.h"

void GlHelper::RenderLoop::run(const GLFWLibrary& library) const
{
    /* Loop until the user closes the window */
    while (!GLFWLibrary::checkWindowIsClosing(mWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        GLFWLibrary::swapBuffers(mWindow);

        /* Poll for and process events */
        library.pollEvents();
    }
}
