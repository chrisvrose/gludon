#include <glShader.hpp>
#include <glad/glad.h>
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
bool glShader::loadFromPath(std::string vspath,std::string fspath){
    std::ifstream vs;
    vs.open(vspath);
    std::stringstream vsstream;
    vsstream<<vs.rdbuf();
    std::string vsstr = vsstream.str();
    // now for the fragment shader
    std::ifstream fs;
    fs.open(fspath);
    std::stringstream fsstream;
    fsstream<<fs.rdbuf();
    std::string fsstr = fsstream.str();

    return this->load(vsstr,fsstr);
    // vsstream
}

bool glShader::load(std::string vsstr, std::string fsstr)
{
    uint vs = compileShader(GL_VERTEX_SHADER, vsstr);
    uint fs = compileShader(GL_FRAGMENT_SHADER, fsstr);

    if (vs == 0 || fs == 0) {
        std::cout << "Program compilation requires vs+fs to compile" << std::endl;
        return (ready = false);
    }
    program = createShaderProgram(vs, fs);

    if (program == 0)
        return (ready = false);
    //delete the intermediate shaders

    glDeleteShader(fs);
    glDeleteShader(vs);
    // return program;

    return (ready=true);
}

uint glShader::createShaderProgram(uint vs, uint fs)
{
    if (vs == 0 || fs == 0) {
        std::cout << "Program compilation requires vs+fs to compile" << std::endl;
        return 0;
    }
    uint program = glCreateProgram();

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);
    return program;
}

uint glShader::compileShader(uint type, std::string& src)
{
    uint shader = glCreateShader(type);
    const char* srcstr = src.c_str();
    glShaderSource(shader, 1, &srcstr, nullptr);

    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        // please, getting compilation stats is usually a pain
        std::cout << "Compilation failed" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << std::endl;
        return 0;
    }

    return shader;
}
bool glShader::use()
{
    if (ready) {
        glUseProgram(program);
    } else {
        std::cout << "Program use when not ready"<<std::endl;
    }
    return ready;
}

glShader::glShader()
{
    program = 0;
    ready = false;
}
glShader::~glShader()
{
    if (ready) {
        std::cout << "Deleting program" << std::endl;
        glDeleteProgram(program);
        ready = false;
    }
}