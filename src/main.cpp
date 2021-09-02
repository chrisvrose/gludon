#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glShader.hpp>
#include <glWindow.hpp>
#include <load_scripts.hpp>
#include <stb_image.h>
// comment this to disable wireframe mode
// #define GL_USE_WIREFRAME

int main(void)
{
    GLWindow window;

    // std::string y = "noper";
    if (!window.loadWindow(640, 480, "Hello world")) {
        std::cout << "Failed to open window";
    }

    // Any init stuff goes here
    float vertices[] = {

        0.f, 0.f,

        0.f, 0.5f, 0.f,

        0.5f, 0.f,

        0.5f, 0.5f, 0.0f,

        0.0f, 0.5f,

        0.0f, 0.0f, 0.5f,

        0.5f, .5f,

        .5f, .0f, .0f
    };

    uint eboindices[] = { 0, 1, 2, 2, 3, 1 };

    uint vbo,
        // remembers all the attribpointers and everything
        vao[2];
    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, &vertices, GL_STATIC_DRAW);

    uint ebo;
    glGenBuffers(1, &ebo);
    // binding with bound arraybuffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(eboindices), eboindices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    glShader shaderProgram;
    shaderProgram.load(
        #include <shaders/simple.vert>
        ,
        #include <shaders/simple.frag>
        );
    shaderProgram.use();
    
    // std::cout << shaderProgram << std::endl;
    // glUseProgram(shaderProgram);
    float a[4] = { 0 };
    // consider this as the game loop
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.window())) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao[0]);

        uint offsetloc = glGetUniformLocation(shaderProgram.getProgram(), "posoff");
        std::cout << offsetloc << std::endl;
        glUniform4fv(offsetloc, 1, a);
        a[0] += 0.001;
        if (a[0] > 1)
            a[0] = -1;
        a[1] += 0.001;
        if (a[1] > 1)
            a[1] = -1;

            // glDrawArrays( GL_TRIANGLES, 0, sizeof(vertices)/sizeof(float));

#ifdef GL_USE_WIREFRAME
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
        glDrawElements(GL_TRIANGLES, sizeof(eboindices) / sizeof(float), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.window());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}