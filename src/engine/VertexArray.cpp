#include "VertexArray.h"


VertexArray::VertexArray() {
    glGenVertexArrays(1, &this->m_renderID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &this->m_renderID);
}

void VertexArray::addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout) const {
    this->bind();
    vertexBuffer.bind();


    const auto& elements{layout.getElements()};
    unsigned int offset{0};

    for (unsigned int i{0}, l{static_cast<unsigned int>(elements.size())}; i < l; ++i) {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(),
                              reinterpret_cast<const void *>(offset));

        offset += element.count * VertexBufferLayoutElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const {
    glBindVertexArray(this->m_renderID);
}

void VertexArray::unBind() const {
    glBindVertexArray(0);
}
