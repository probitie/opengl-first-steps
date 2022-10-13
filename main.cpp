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


    // === prepare data before rendering === //

    // 2D points (for rectangle)
    float vertices1[]
    {
       0.5f,   0.5f, 0.0f,  //        top first
       0.9f,  -0.5f, 0.0f,  // bottom left first
       0.1f,  -0.5f, 0.0f,  // bottom right first

    };
    float vertices2[]
    {
        -0.5f,   0.5f, 0.0f,  //        top second
        -0.9f,  -0.5f, 0.0f,  // bottom left second
        -0.1f,  -0.5f, 0.0f   // bottom right second

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

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
        // start using our shader program (but in the loop)
        glUseProgram(shaderProgram);

        // draw the first triangle from the first VAO
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

    glfwTerminate();

    return 0;
}
