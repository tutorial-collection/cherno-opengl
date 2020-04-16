#include "IndexBuffer.h"
#include "Renderer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
: m_count{count} {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint), "C++ unsigned int does not match GLuint");

    glGenBuffers(1, &this->m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &this->m_rendererID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_rendererID);
}

void IndexBuffer::unBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
