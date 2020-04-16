#ifndef OPENGLTHECHERNO_TEXTURE_H
#define OPENGLTHECHERNO_TEXTURE_H

#include "Renderer.h"

class Texture {
private:
    unsigned int m_rendererID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width;
    int m_height;
    int m_BPP; // Bits per pixel

public:
    Texture(const std::string &filePath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unBind() const;


    // Getters and setters
    int getWidth() const { return this->m_width; };
    int getHeight() const { return this->m_height; };
};


#endif //OPENGLTHECHERNO_TEXTURE_H
