#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <SquareObject.hpp>
#include <glShader.hpp>
#include <glTexture.hpp>
#include <glWindow.hpp>
#include <load_scripts.hpp>
// comment this to disable wireframe mode
// #define GL_USE_WIREFRAME

int main(void)
{
    GLWindow window;

    // std::string y = "noper";
    std::unordered_map<int, int> window_hints;
    window_hints[GLFW_RESIZABLE] = GLFW_TRUE;
    window_hints[GLFW_DECORATED] = GLFW_TRUE;
    if (!window.loadWindow(640, 480, "Hello world", window_hints)) {
        std::cout << "Failed to open window";
    }

    glm::vec4 pos(0.f);
    SquareObject so(pos);
    

    // consider this as the game loop
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.window())) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        so.draw();
        // move the state around a bit
        so.changeState();

        // set to polygon if required
#ifdef GL_USE_WIREFRAME
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

        /* Swap front and back buffers */
        glfwSwapBuffers(window.window());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}