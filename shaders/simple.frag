// just color it nicely red
#version 330 core

in vec4 colora;
layout(location=0) out vec4 color;
void main(){
    color = colora;
}