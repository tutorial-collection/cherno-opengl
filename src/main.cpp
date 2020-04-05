#define GLEW_BUILD
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


// Constants
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;



/**
 * Compile a single shader.
 * @param type The type of the shader.
 * @param shader The shader in string format.
 * @return The shader id.
 */
static unsigned int CompileShader(unsigned int type, const std::string& shader) {
    unsigned int shaderId = glCreateShader(type);
    const char* shaderCString = shader.c_str();

    glShaderSource(shaderId, 1, &shaderCString, nullptr);
    glCompileShader(shaderId);

    // Error handling
    int result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shaderId, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

/**
 * Create a shader by it's vertex- and fragmentShaders.
 * @param vertexShader The vertex shader.
 * @param fragmentShader The fragment shader.
 * @return The shader id.
 */
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program{glCreateProgram()};
    unsigned int vShader{CompileShader(GL_VERTEX_SHADER, vertexShader)};
    unsigned int fShader{CompileShader(GL_FRAGMENT_SHADER, fragmentShader)};

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glValidateProgram(program);

    // Delete the shaders, you can do this because they are now linked into a program.
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}


/**
 * class Main
 * @author Ingo Andelhofs
 */
int main() {
    GLFWwindow *window;

    /* Initialize GLFW */
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "The Cherno OpenGL", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to initialize GLFW window" << std::endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    if(glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    /* Log the OpenGL version */
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Initialize vertex buffer */
    float trianglePositions[6] {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer); // Create one buffer with the address of buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // Binds the buffer as the current used buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), trianglePositions, GL_STATIC_DRAW); // Set the data of the buffer

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr); // Setup the layout of the triangle positions

    /* Creating shader */
    std::string vertexShader{
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main() {\n"
        "   gl_Position = position;\n"
        "}\n"
    };

    std::string fragmentShader{
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main() {\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n"
    };

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Modern OpenGL triangle with shaders */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}