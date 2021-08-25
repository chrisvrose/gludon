#include <string>

/**
 * Compile a given shader
*/
uint compileShader(uint type, std::string& src);
/**
 * Compile a shader program from a given vertex and fragment source
*/
uint createShaderProgram(std::string& vsstr,std::string& fsstr);
/**
 * Create shader program from compiled shaders
*/
uint createShaderProgram(uint vs,uint fs);
