#include <glad/glad.h>
#include <KHR/khrplatform.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

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


    // =========== vertex shader ========== //

    // source code
    const char * vertexShaderSourceFirst = "# version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "out vec4 vertexColor;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos, 1.0);\n"
            "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
            "}\0";
    const char * vertexShaderSourceSecond = "# version 330 core\n"
                                            "layout (location = 0) in vec3 aPos;\n"
                                            "layout (location = 1) in vec3 aColor;\n"
                                            "out vec3 outColor;\n"
                                            "void main()\n"
                                            "{\n"
                                            "    gl_Position = vec4(aPos, 1.0);\n"
                                            "    outColor = aColor;\n"
                                            "}\0";;

    // shader object id
    GLuint vertexShaderFirst, vertexShaderSecond;

    vertexShaderFirst = glCreateShader(GL_VERTEX_SHADER);
    vertexShaderSecond = glCreateShader(GL_VERTEX_SHADER);

    // write source code to shader object
    glShaderSource(vertexShaderFirst, 1, &vertexShaderSourceFirst, NULL);
    glShaderSource(vertexShaderSecond, 1, &vertexShaderSourceSecond, NULL);

    // compile it at runtime
    glCompileShader(vertexShaderFirst);
    glCompileShader(vertexShaderSecond);

    // check shader compilation errors

    GLint success, successSecond;;
    const GLint infoLogSize = 512;
    GLchar infoLog[infoLogSize]{};

    glGetShaderiv(vertexShaderFirst, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShaderFirst, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::FIRST::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(vertexShaderFirst, GL_COMPILE_STATUS, &successSecond);

    if (!successSecond)
    {
        glGetShaderInfoLog(vertexShaderSecond, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::SECOND::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //


    // ==================================== //


    // ========== fragment shader ========= //

    const char* fragmentShaderSourceFirst = "#version 330 core\n"
                                       "in vec4 vertexColor;\n"
                                       "out vec4 FragColor;\n"
                                       "uniform vec4 outColor;  // we can set this in our actual code \n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = outColor;\n"
                                       "}\n";

    const char* fragmentShaderSourceSecond = "#version 330 core\n"
                                             "in vec4 outColor;\n"
                                             "out vec4 FragColor;\n"
                                             "uniform vec4 outColor;  // we can set this in our actual code \n"
                                             "void main()\n"
                                             "{\n"
                                             "    FragColor = vec4(outColor, 1.0);\n"
                                             "}\n";

    // shader id
    GLuint fragmentShaderFirst, fragmentShaderSecond;
    fragmentShaderFirst = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShaderSecond = glCreateShader(GL_FRAGMENT_SHADER);

    // write source code to shader object
    glShaderSource(fragmentShaderFirst, 1, &fragmentShaderSourceFirst, NULL);

    glShaderSource(fragmentShaderSecond, 1, &fragmentShaderSourceSecond, NULL);

    // runtime compiling
    glCompileShader(fragmentShaderFirst);
    glCompileShader(fragmentShaderSecond);

    // check errors for this shader

    glGetShaderiv(fragmentShaderFirst, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderFirst, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::FIRST::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShaderFirst, GL_COMPILE_STATUS, &successSecond);
    if (!successSecond)
    {
        glGetShaderInfoLog(fragmentShaderSecond, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::SECOND::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ==================================== //


    // == add shaders to the final shader program == //

    // shader program id
    GLuint shaderProgram, shaderProgramSecond;
    shaderProgram = glCreateProgram();

    shaderProgramSecond = glCreateProgram();

    // linking shadersshaderProgramSecond
    glAttachShader(shaderProgram, vertexShaderFirst);
    glAttachShader(shaderProgram, fragmentShaderFirst);
    glLinkProgram(shaderProgram);

    glAttachShader(shaderProgramSecond, vertexShaderSecond);
    glAttachShader(shaderProgramSecond, fragmentShaderSecond);
    glLinkProgram(shaderProgramSecond);

    // check errors
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    glGetShaderiv(shaderProgramSecond, GL_LINK_STATUS, &successSecond);

    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::FINAL::FIRST::LINKING_FAILED\n" << infoLog << std::endl;
    }
    if (!successSecond)
    {
        glGetShaderInfoLog(shaderProgramSecond, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::FINAL::SECOND::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // ==================================== //



    // delete shaders after linking
    glDeleteShader(vertexShaderFirst);
    glDeleteShader(fragmentShaderFirst);
    glDeleteShader(fragmentShaderSecond);


    // === prepare data before rendering === //

    // 2D points (for rectangle)

    // glowing triangle
    float vertices1[]
    {
       0.5f,   0.5f, 0.0f,  //        top first
       0.9f,  -0.5f, 0.0f,  // bottom left first
       0.1f,  -0.5f, 0.0f   // bottom right first

    };


    // gradient triangle
    float vertices2[]
    {  //    vertices  //  //    colors    //
        -0.5f,   0.5f, 0.0f,  1.0f, 0.0f, 0.0f,//        top second
        -0.9f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom left second
        -0.1f,  -0.5f, 0.0f,  0.0f, 0.0f, 1.0f // bottom right second

    };

    // vertex buffer objects

    // generate id for the buffer
    GLuint VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);


    // first buffers (for first triangle)
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // we are not using EBO buffer here
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    // write our triange to that buffer
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // second buffers (for second triangle)
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // ==================================== //

    // specify data which
    // will go to the shader program
    // ( especially to the vertex shader )
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // uncomment if u want to draw only bounds
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // main loop
    while(!glfwWindowShouldClose(window))
    {
        // user input
        processInput(window);


        // the rendering stuff happens here
        glClearColor(0.2f, 0.6f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLfloat timeValue = glfwGetTime();
        float redValue = (std::sin(timeValue) / 2.0f + 0.5f);
        float greenValue = (std::cos(timeValue) / 2.0f + 0.5f);
        float blueValue = (std::sin(timeValue+1123) / 2.0f + 0.5f);
        //int colorVariableLocation = glGetUniformLocation(shaderProgram, "outColor");
        //glUniform4f(colorVariableLocation, redValue, greenValue, blueValue, 1.0f);


        // start using our shader program (but in the loop)
        //glUseProgram(shaderProgram);
        // draw the first triangle from the first VAO
        //glBindVertexArray(VAOs[0]);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        //int colorVariableLocationSecond = glGetUniformLocation(shaderProgramSecond, "outColor");
        //glUniform4f(colorVariableLocationSecond, greenValue, blueValue, redValue, 0.8f); // colors in a wrong order

        glUseProgram(shaderProgramSecond);

        // draw the second triangle from the second VAO
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers, check events
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glad_glDeleteVertexArrays(2, VAOs);
    glad_glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgramSecond);

    glfwTerminate();

    return 0;
}
