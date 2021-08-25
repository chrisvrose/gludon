#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glWindow.hpp>
#include <load_scripts.hpp>
int main(void)
{
    GLWindow window;

    // std::string y = "noper";
    if (!window.loadWindow(640, 480, "Hello world")) {
        std::cout << "Failed to open window";
    }

    // Any init stuff goes here
    float vertices[] = {
        -0.0f,
        -0.5f,

        0.5f,
        -0.5f,

        0.0f,
        0.5f,
    };

    uint vbo,vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    std::string fb =
#include <shaders/simple.frag>
        ;

    std::string vb =
#include <shaders/simple.vert>
        ;

    uint shaderProgram = createShaderProgram(vb,fb);
    std::cout<<shaderProgram<<std::endl;
    glUseProgram(shaderProgram);

    // consider this as the game loop
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.window())) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window.window());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    return 0;
}