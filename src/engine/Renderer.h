#ifndef OPENGLTHECHERNO_RENDERER_H
#define OPENGLTHECHERNO_RENDERER_H

#include <GL/glew.h>
#include "../error/error.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Renderer {
public:
    static void enableDebugCallback();
    void draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shader &shader) const;
    void clear() const;

private:
    static void GLAPIENTRY debugCallbackMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
                                                GLsizei length, const char *message, const void *userParam);
};


#endif //OPENGLTHECHERNO_RENDERER_H
