#ifndef OPENGLTHECHERNO_INDEXBUFFER_H
#define OPENGLTHECHERNO_INDEXBUFFER_H


class IndexBuffer {
private:
    unsigned int m_rendererID;
    unsigned int m_count;

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unBind() const;

    unsigned int getCount() const { return m_count; };
};


#endif //OPENGLTHECHERNO_INDEXBUFFER_H
