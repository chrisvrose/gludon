#version 330 core

layout (location=0) in vec4 posit;
layout (location=1) in vec4 colorin;
uniform vec4 posoff;
out vec4 colora;

void main(){
    gl_Position = posit+posoff;
    colora=colorin;
}