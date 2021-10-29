#pragma once
#include<iostream>
#include<glm/vec4.hpp>
#include <glShader.hpp>
#include <glTexture.hpp>
class SquareObject {
private:
    bool ready;
    glm::vec4 worldPosition;
    uint vao;
    glShader shaderProgram;
    glTexture tex;

    uint vbo;
    // remembers all the attribpointers and everything
    // uint vao[2];

    // ebo saves memory by representing an array of pointers to orig data
    uint ebo;

    float internalState[4] = {0};
    
    //vertices
    float vertices[8*4] = {

        0.f, 0.f, 0.f,

        0.f, 0.5f, 0.f, 0.0f, 0.0f,

        0.5f, 0.f, 0.f,

        0.5f, 0.5f, 0.0f, 1.f, 0.f,

        0.0f, 0.5f, 0.f,

        0.0f, 0.0f, 0.5f, .0f, 1.f,

        0.5f, .5f, 0.f,

        .5f, .0f, .0f, 1.f, 1.f
    };
    uint eboindices[6] = { 0, 1, 2, 2, 3, 1 };
public:
    SquareObject(glm::vec4 a);
    void draw();

    void changeState(){
        internalState[0] += 0.001;
        if (internalState[0] > 1)
            internalState[0] = -1;
        internalState[1] += 0.001;
        if (internalState[1] > 1)
            internalState[1] = -1;
    }
};