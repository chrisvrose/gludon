#include<string>
#pragma once

/** Static variable for cout snippet*/
extern char glTexHeader[];

class glTexture{
    private:
    bool ready;
    int width;
    int height;
    int components;
    std::string filename;
    unsigned char* data;
    unsigned int gltexid;
    public:
    glTexture() = delete;
    glTexture(std::string filename);
    unsigned int useTexture();
    void use();
    ~glTexture();
};