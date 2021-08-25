#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glWindow.hpp>
#include <load_scripts.hpp>
int main(void)
{
    GLWindow window;

    std::string y = "noper";
    if (!window.loadWindow(640, 480, "Hello world")) {
        std::cout << "Failed to open window";
    }

    // Any init stuff goes here
    // float vertices[] = {
    //     -0.5f,
    //     -0.5f,
    //     0.0f,
    //     0.5f,
    //     -0.5f,
    //     0.0f,
    //     0.0f,
    //     0.5f,
    //     0.0f
    // };
    // uint vbo;
    // glGenBuffers(1,&vbo);
    // glBindBuffer(GL_ARRAY_BUFFER,vbo);


    // consider this as the game loop
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.window()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.window());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}