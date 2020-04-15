#ifndef OPENGLTHECHERNO_VERTEXARRAY_H
#define OPENGLTHECHERNO_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class VertexArray {
private:
    unsigned int m_renderID{};

public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unBind() const;
    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) const;
};


#endif //OPENGLTHECHERNO_VERTEXARRAY_H
