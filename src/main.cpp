#define GLEW_BUILD

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "error.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"


// Constants
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;


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
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    /* Log the OpenGL version */
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Init error handling
    Renderer::enableDebugCallback();


    /* Initialize vertex buffer */
    float trianglePositions[]{
        -0.5f, -0.5f, // Vertex 1
        0.5f, -0.5f, // Vertex 2
        0.5f, 0.5f, // Vertex 3
        -0.5f, 0.5f, // Vertex 4
    };


    // Indexes
    // First draw a triangle with Vertexes 1, 2, 3
    // Second draw a triangle with Vertexes 3, 4, 1
    // This forms a square
    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };


    VertexArray vao{};
    VertexBuffer triangleBuffer{trianglePositions, 4 * 2 * sizeof(float)};

    VertexBufferLayout triangleLayout{};
    triangleLayout.push<float>(2);
    vao.addBuffer(triangleBuffer, triangleLayout);

    IndexBuffer triangleIndexBuffer{indices, 6};


    Shader shader{"../res/shaders/Basic.shader"};
    shader.bind();
    shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);


    // Unbind all
    vao.unBind();
    shader.unBind();
    triangleBuffer.unBind();
    triangleIndexBuffer.unBind();


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


        // Bind shader, buffer and index buffer
        shader.bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        vao.bind();
        triangleIndexBuffer.bind();

        // Draw call
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // Count of indices, buffer is already bound


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // Animate color
        if (r > 1.0f)
            rIncrement = -0.05f;
        if (r < 0.0f)
            rIncrement = 0.05f;

        r += rIncrement;

        // Frame counter
        if (frame % 60 == 0)
            std::cout << "60 frames: " << frame / 60 << std::endl;
        ++frame;
    }

    glfwTerminate();
    return 0;
}