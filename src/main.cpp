#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
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

    // all the vertices and associated data
    float vertices[] = {

        0.f, 0.f, 0.f,

        0.f, 0.5f, 0.f, 0.0f, 0.0f,

        0.5f, 0.f, 0.f,

        0.5f, 0.5f, 0.0f, 1.f, 0.f,

        0.0f, 0.5f, 0.f,

        0.0f, 0.0f, 0.5f, .0f, 1.f,

        0.5f, .5f, 0.f,

        .5f, .0f, .0f, 1.f, 1.f
    };
    // elementwise array
    uint eboindices[] = { 0, 1, 2, 2, 3, 1 };

    uint vbo,
        // remembers all the attribpointers and everything
        vao[2];
    // create two and place in array
    glGenVertexArrays(2, vao);
    // bind the first one for use (stores the attrib pointers)
    glBindVertexArray(vao[0]);
    // generates a vbo
    glGenBuffers(1, &vbo);
    // bind it as a vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // pass data to it
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, &vertices, GL_STATIC_DRAW);

    // ebo saves memory by representing an array of pointers to orig data
    uint ebo;
    glGenBuffers(1, &ebo);
    // binding with bound arraybuffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(eboindices), eboindices, GL_STATIC_DRAW);

    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    glEnableVertexAttribArray(0);

    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    
    // texture uv coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
    // create a shader program for shading our vertices
    glShader shaderProgram;
    shaderProgram.loadFromPath(
        "shaders/simple.vert",
        "shaders/simple.frag");    
    shaderProgram.use();

    // load up a texture
    std::string s = "res/img/container.jpg";
    glTexture tex(s);
    // set as active texture for drawing
    tex.use();
    // std::cout << shaderProgram << std::endl;
    // glUseProgram(shaderProgram);


    // small state array - position offset (xyzw (what the hell is w?))
    float a[4] = { 0 };

    // consider this as the game loop
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.window())) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao[0]);
        
        // get uniform position
        uint offsetloc = glGetUniformLocation(shaderProgram.getProgram(), "posoff");
        // set it to 'a'
        glUniform4fv(offsetloc, 1, a);
        // modify a now
        a[0] += 0.001;
        if (a[0] > 1)
            a[0] = -1;
        a[1] += 0.001;
        if (a[1] > 1)
            a[1] = -1;
        // draw current bound vbo
        // glDrawArrays( GL_TRIANGLES, 0, sizeof(vertices)/sizeof(float));
        
        // set to polygon if required
#ifdef GL_USE_WIREFRAME
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
        // draw from currently bound ebo which is using currently bound vbo
        glDrawElements(GL_TRIANGLES, sizeof(eboindices) / sizeof(float), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.window());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}