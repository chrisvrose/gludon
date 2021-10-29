#include <SquareObject.hpp>

#include <glad/glad.h>
SquareObject::SquareObject(glm::vec4 worldPos)
    : tex("res/img/container.jpg")
{
    worldPosition = worldPos;
    ready = false;

    // create two and place in array
    glGenVertexArrays(1, &vao);
    // bind the first one for use (stores the attrib pointers)
    glBindVertexArray(vao);
    // generates a vbo
    glGenBuffers(1, &vbo);
    // bind it as a vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // pass data to it
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, &vertices, GL_STATIC_DRAW);

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
    // glShader shaderProgram;
    shaderProgram.loadFromPath(
        "shaders/simple.vert",
        "shaders/simple.frag");
    shaderProgram.use();

    tex.use();
    ready = true;
}

void SquareObject::draw()
{
    // bind the arrays
    glBindVertexArray(vao);

    shaderProgram.use();
    tex.use();

    // get uniform position
    uint offsetloc = glGetUniformLocation(shaderProgram.getProgram(), "posoff");
    // set it to 'a'
    glUniform4fv(offsetloc, 1, internalState);

    // draw the damn thing
    glDrawElements(GL_TRIANGLES, sizeof(eboindices) / sizeof(float), GL_UNSIGNED_INT, 0);
}
