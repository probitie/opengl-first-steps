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

    try
    {
        // open files
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        // read files into streams
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();

        // close files
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // convert streams to strings
        vertexCode = vertexStream.str();
        fragmentCode = vertexStream.str();
    }
    catch(std::ifstream::failure e)
    {
        errorlog("can not read one of shaders: " << e.what());
    }
    // -----------------------------------------------------


    // compile shaders
    // -----------------------------------------------------
    GLuint vertex, fragment;
    GLint success;
    char infoLog[512];

    // vertex shader
}
