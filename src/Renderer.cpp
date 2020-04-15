#include "Renderer.h"
#include <iostream>


/**
 * Enable the debug callback for OpenGL Error handling.
 */
void Renderer::enableDebugCallback() {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(Renderer::debugCallbackMessage, nullptr);
}


/**
 * Log the OpenGL Error to the console.
 * @param source
 * @param type
 * @param id
 * @param severity
 * @param length
 * @param message
 * @param userParam
 */
void GLAPIENTRY Renderer::debugCallbackMessage(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const char *message,
        const void *userParam) {

    std::cerr
            << "GL ERROR CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") << std::endl
            << "GL ERROR MESSAGE: " << message << std::endl;

//    std::cerr
//        << source << std::endl
//        << type << std::endl
//        << severity << std::endl
//        << length << std::endl
//        << id << std::endl
//        << userParam << std::endl;


    STOP("OpenGL Error");
}



