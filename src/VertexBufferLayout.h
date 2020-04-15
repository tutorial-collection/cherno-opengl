#ifndef OPENGLTHECHERNO_VERTEXBUFFERLAYOUT_H
#define OPENGLTHECHERNO_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>
#include "error.h"


struct VertexBufferLayoutElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
            default: break;
        }
        STOP("@VertexArrayLayout: unknown type");
        return 0;
    };
};


class VertexBufferLayout {
private:
    std::vector<VertexBufferLayoutElement> m_elements;
    unsigned int m_stride;

public:
    VertexBufferLayout() : m_stride{0} {};


    // Push templates
    template<typename T>
    void push(unsigned int count) { static_assert(false); }

    template<>
    void push<float>(unsigned int count) {
        m_elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_stride += VertexBufferLayoutElement::getSizeOfType(GL_FLOAT) * count;
    }

    template<>
    void push<unsigned int>(unsigned int count) {
        m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_stride += VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_INT) * count;
    }

    template<>
    void push<unsigned char>(unsigned int count) {
        m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_stride += VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
    }


    // Getters and Setters
    const std::vector<VertexBufferLayoutElement>& getElements() const { return m_elements; };
    unsigned int getStride() const { return m_stride; }
};


#endif //OPENGLTHECHERNO_VERTEXBUFFERLAYOUT_H
