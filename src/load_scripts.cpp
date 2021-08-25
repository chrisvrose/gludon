#include <glad/glad.h>
#include <iostream>
#include <load_scripts.hpp>

uint compileShader(uint type, std::string& src)
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

uint createShaderProgram(std::string& vsstr, std::string& fsstr)
{
    uint vs = compileShader(GL_VERTEX_SHADER, vsstr);
    uint fs = compileShader(GL_FRAGMENT_SHADER, fsstr);

    if (vs == 0 || fs == 0) {
        std::cout << "Program compilation requires vs+fs to compile" << std::endl;
        return 0;
    }
    uint program = createShaderProgram(vs, fs);

    if(program==0) return program;
    //delete the intermediate shaders

    
    glDeleteShader(fs);
    glDeleteShader(vs);
    return program;
}

uint createShaderProgram(uint vs, uint fs)
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
