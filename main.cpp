#include <glad/glad.h>
#include <KHR/khrplatform.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // all this means as OpenGL 3.3 (can be higher) so GLFW 3.3 (can be higher too)

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "hello triangle - OpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Can not create a window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Can not initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // === prepare data before rendering === //

    // 2D triangle
    float vertices[]
    {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f

    };

    // vertex buffer objects

    // generate id for the buffer
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // generate id for the buffer
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // now whenever we call GL_ARRAY_BUFFER
    // the VBO buffer will be invoked
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // write our triange to that buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    // ==================================== //


    // =========== vertex shader ========== //

    // source code
    const char * vertexShaderSource = "# version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

    // shader object id
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // write source code to shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // compile it at runtime
    glCompileShader(vertexShader);

    // check shader compilation errors

    GLint success;
    const GLint infoLogSize = 512;
    GLchar infoLog[infoLogSize]{};

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //


    // ==================================== //


    // ========== fragment shader ========= //

    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n";

    // shader id
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // write source code to shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // runtime compiling
    glCompileShader(fragmentShader);

    // check errors for this shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ==================================== //


    // == add shaders to the final shader program == //

    // shader program id
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    // linking shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // check errors
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::FINAL::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // ==================================== //

    // start using our shader program
    glUseProgram(shaderProgram);

    // delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // specify data which
    // will go to the shader program
    // ( especially to the vertex shader )
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // main loop
    while(!glfwWindowShouldClose(window))
    {
        // user input
        processInput(window);


        // the rendering stuff happens here


        glClearColor(0.2f, 0.6f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers, check events
        glfwPollEvents();
        glfwSwapBuffers(window);
    }



    glfwTerminate();

    return 0;
}
