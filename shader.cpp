#include "shader.h"

Shader::~Shader()
{
    glDeleteProgram(ID);
}

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
        fragmentCode = fragmentStream.str();
    }
    catch(std::ifstream::failure e)
    {
        errorlog("can not read one of shaders: " << e.what());
    }
    // -----------------------------------------------------
    const char * vertexCodeCStr = vertexCode.c_str();
    const char * fragmentCodeCStr = fragmentCode.c_str();


    // compile shaders
    // -----------------------------------------------------
    GLuint vertex, fragment;
    GLint success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCodeCStr, NULL);
    glCompileShader(vertex);

    // output errors
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        errorlog("vertex compilation failed");
    }

    // the same for fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCodeCStr, NULL);
    glCompileShader(fragment);

    // output errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        errorlog("fragment compilation failed");
    }
    // -----------------------------------------------------


    // link shaders to a shader program
    // -----------------------------------------------------
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // output errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        errorlog("shader linking failed");
    }
    // -----------------------------------------------------


    // delete unnecessary shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
