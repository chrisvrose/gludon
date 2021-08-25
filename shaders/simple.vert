#version 330 core

layout (location=0) in vec4 posit;

void main(){
    gl_Position = posit;
}