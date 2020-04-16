#define GLEW_BUILD

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <iostream>

#include "engine/Renderer.h"
#include "utils/RGBA.h"
#include "engine/Texture.h"


// Constants
const int SCALE = 2;
const GLuint WIDTH = 1080 * SCALE;
const GLuint HEIGHT = 720 * SCALE;


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
    std::cout << Renderer::getGLVersion() << std::endl;

    // Init error handling
    Renderer::enableDebugCallback();


    /* Initialize vertex buffer */
    float trianglePositions[]{
        100.0f, 100.0f, 0.0f, 0.0f, // Vertex 1
        500.0f, 100.0f, 1.0f, 0.0f, // Vertex 2
        500.0f, 500.0f, 1.0f, 1.0f, // Vertex 3
        100.0f, 500.0f, 0.0f, 1.0f // Vertex 4
    };


    // Indexes
    // First draw a triangle with Vertexes 1, 2, 3
    // Second draw a triangle with Vertexes 3, 4, 1
    // This forms a square
    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };


    // BLENDING
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);


    VertexArray vao{};
    VertexBuffer triangleBuffer{trianglePositions, 4 * 4 * sizeof(float)};

    VertexBufferLayout triangleLayout{};
    triangleLayout.push<float>(2);
    triangleLayout.push<float>(2);
    vao.addBuffer(triangleBuffer, triangleLayout);

    IndexBuffer triangleIndexBuffer{indices, 6};


    // Projection matrix
    glm::mat4 projectionMatrix{glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f)};
    glm::vec4 vertexPositions{100.0f, 100.0f, 0.0f, 1.0f};

    glm::vec4 result{projectionMatrix * vertexPositions};


    Shader shader{"../res/shaders/Basic.shader"};
    shader.bind();
    shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.setUniformMat4f("u_MVP", projectionMatrix);


    Texture texture{"../res/textures/brick0.jpg"};
    texture.bind();
    shader.setUniform1i("u_Texture", 0); // Match slot with 0


    // Unbind all
    vao.unBind();
    shader.unBind();
    triangleBuffer.unBind();
    triangleIndexBuffer.unBind();

    // Colors
    RGBA rgba{0.0f, 0.3f, 0.8f, 1.0f};

    Renderer renderer{};
    float rIncrement = 0.05f;
    unsigned int frame = 0;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        renderer.clear();

        shader.bind();
        shader.setUniform4f("u_Color", rgba.getGLR(), rgba.getGLG(), rgba.getGLB(), rgba.getGLA());

        renderer.draw(vao, triangleIndexBuffer, shader);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


        // Animate color
        if (rgba.getGLR() > 1.0f) rIncrement = -0.05f;
        if (rgba.getGLR() < 0.0f) rIncrement = 0.05f;
        rgba.setR( rgba.getGLR() + rIncrement );


        // Frame counter
        if (frame % 60 == 0) {
            std::cout << "60 frames: " << frame / 60 << std::endl;
        }
        ++frame;
    }

    glfwTerminate();
    return 0;
}