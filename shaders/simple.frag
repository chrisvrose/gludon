// just color it nicely red
#version 330 core

in vec4 colora;
in vec2 texc;
// out vec4 FragColor;

uniform sampler2D ourTexture;

layout(location=0) out vec4 color;

void main(){
    // color = colora;
    color = texture(ourTexture, texc) * vec4(colora)*2;
}