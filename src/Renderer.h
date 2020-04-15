#ifndef OPENGLTHECHERNO_RENDERER_H
#define OPENGLTHECHERNO_RENDERER_H

#include <GL/glew.h>
#include "error.h"


class Renderer {
public:
    static void enableDebugCallback();

private:
    static void GLAPIENTRY debugCallbackMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
                                                GLsizei length, const char *message, const void *userParam);
};


#endif //OPENGLTHECHERNO_RENDERER_H
