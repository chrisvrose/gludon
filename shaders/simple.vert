#version 330 core

layout (location=0) in vec4 posit;
layout (location=1) in vec4 colorin;
layout (location = 2) in vec2 aTexCoord;
uniform vec4 posoff;


out vec4 colora;
out vec2 texc;

void main(){
    gl_Position = posit+posoff;
    colora=colorin;
    texc=aTexCoord;
}