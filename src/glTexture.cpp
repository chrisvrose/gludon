#define STBI_NO_PSD
#define STBI_NO_BMP
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#define STB_IMAGE_IMPLEMENTATION
#include <glTexture.hpp>
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>


char glTexHeader[] = "GLT>";


glTexture::glTexture(std::string filename)
{
    ready = false, width = 0, height = 0, gltexid = 0, components = 0, data = nullptr;
    this->filename = filename;
    int ok = stbi_info(filename.c_str(), &width, &height, &components);
    if (!ok) {
        std::cout << glTexHeader << filename << " not queryable" << std::endl;
        return;
    }

    data = stbi_load(filename.c_str(), &width, &height, &components, 3);

    glGenTextures(1, &gltexid);
    glBindTexture(GL_TEXTURE_2D, gltexid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    std::cout<<glTexHeader<<"Image ready:"<<filename<<std::endl;
    ready=true;
}

void glTexture::bind()
{
    if (ready) {
        glBindTexture(GL_TEXTURE_2D, gltexid);
    }else{
        std::cout<<"Binding invalid texture";
    }
}

glTexture::~glTexture()
{
    std::cout << glTexHeader << "Cleaning image " << filename << std::endl;
    if (data != nullptr) {
        stbi_image_free(data);
    }
    if (ready)
        glDeleteTextures(1, &gltexid);
}

unsigned int glTexture::useTexture()
{
    if (!ready) {
        std::cout << "Texture at " << filename << std::endl;
    }
    return gltexid;
}