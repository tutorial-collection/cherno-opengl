#ifndef OPENGLTHECHERNO_VERTEXBUFFER_H
#define OPENGLTHECHERNO_VERTEXBUFFER_H


class VertexBuffer {
private:
    unsigned int m_rendererID;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unBind() const;
};


#endif //OPENGLTHECHERNO_VERTEXBUFFER_H