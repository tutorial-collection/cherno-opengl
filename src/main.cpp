#define GLEW_BUILD
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Macro's
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

// Constants
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};


// Error handling
static void GLClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL Error]: " << error << " " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}


static ShaderProgramSource ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)) {
        // If is is a shader define
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}


/**
 * Compile a single shader.
 * @param type The type of the shader.
 * @param shader The shader in string format.
 * @return The shader id.
 */
static unsigned int CompileShader(unsigned int type, const std::string& shader) {
    GLCall(unsigned int shaderId = glCreateShader(type));
    const char* shaderCString = shader.c_str();

    GLCall(glShaderSource(shaderId, 1, &shaderCString, nullptr));
    GLCall(glCompileShader(shaderId));

    // Error handling
    int result;
    GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));

        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(shaderId, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(shaderId));
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
    GLCall(unsigned int program{glCreateProgram()});
    GLCall(unsigned int vShader{CompileShader(GL_VERTEX_SHADER, vertexShader)});
    GLCall(unsigned int fShader{CompileShader(GL_FRAGMENT_SHADER, fragmentShader)});

    GLCall(glAttachShader(program, vShader));
    GLCall(glAttachShader(program, fShader));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    // Delete the shaders, you can do this because they are now linked into a program.
    GLCall(glDeleteShader(vShader));
    GLCall(glDeleteShader(fShader));

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

    // swap interval
    glfwSwapInterval(1);


    /* Initialize GLEW */
    if(glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    /* Log the OpenGL version */
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Initialize vertex buffer */
    float trianglePositions[] {
        // First triangle
        -0.5f, -0.5f, // Vertex 1
        0.5f, -0.5f, // Vertex 2
        0.5f, 0.5f, // Vertex 3
        // Second triangle
        // 0.5f, 0.5f, Duplicate
        -0.5f, 0.5f, // Vertex 4
        // -0.5f, -0.5f, Duplicate
    };


    // Indexes
    // First draw a triangle with Vertexes 1, 2, 3
    // Second draw a triangle with Vertexes 3, 4, 1
    // This forms a square
    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };


    // Buffer
    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer)); // Create one buffer with the address of buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); // Binds the buffer as the current used buffer
    GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), trianglePositions, GL_STATIC_DRAW)); // Set the data of the buffer


    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr)); // Setup the layout of the triangle positions


    // Index buffer
    unsigned int ibo; // Index buffer object
    GLCall(glGenBuffers(1, &ibo)); // Create one buffer for the index buffer object
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)); // Binds the buffer as the current used buffer, element array buffer
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW)); // Set the data of the buffer


    /* Creating shader */
    // Relative path from the /build folder where the exe lives.
    ShaderProgramSource source = ParseShader("../res/shaders/Basic.shader");

    GLCall(unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource));
    GLCall(glUseProgram(shader));


    // Uniforms
    // Uniforms are set per draw

    // Uniform with 4 floats (vec4 in shader)
    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

    // Animated colors
    float r = 0.0f;
    float g = 0.8f;
    float b = 0.8f;

    float rIncrement = 0.05f;

    unsigned int frame = 0;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Modern OpenGL triangle with shaders */
        // glDrawArrays(GL_TRIANGLES, 0, 6); // From triangle 0 to 6!

        // Animate color
        if (r > 1.0f)
            rIncrement = -0.05f;
        if (r < 0.0f)
            rIncrement = 0.05f;

        r += rIncrement;

        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // Count of indices, buffer is already bound


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        if (frame % 60 == 0)
            std::cout << "60 frames: " << frame / 60 << std::endl;
        ++frame;
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}