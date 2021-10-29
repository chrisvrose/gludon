
#pragma once

#include<string>
#include<glad/glad.h>
class glShader{
    private:
    bool ready;
    uint program;
    uint compileShader(uint type, std::string& src);
    uint createShaderProgram(uint vs, uint fs);
public:
    glShader();
    ~glShader();
    /**
     * Set program as active
    */
    bool use();

    uint getProgram(){return program;}
    bool load(std::string vs,std::string fs);
    bool loadFromPath(std::string vspath,std::string fspath);
};