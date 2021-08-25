#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <load_scripts.hpp>
#include<glWindow.hpp>
int main(void)
{
    GLWindow window;
    if(!window.loadWindow(640,480,"Hello world")){
        std::cout<<"Failed to open window";
    }

    // consider this as the game loop
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.window())) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.window());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}