#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // read vertex/fragment shaders from the path
    // ------------------------------------------

    std::string vertexCode, fragmentCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    // force enable exceptions
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    debuglog("first log " << 10);
    warnlog("second log " << 10);
    errorlog("3 log " << 10);



}
