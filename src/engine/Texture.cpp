#include <STB/stb_image.h>
#include "Texture.h"


Texture::Texture(const std::string &filePath)
:m_rendererID{0}, m_filePath{filePath}, m_localBuffer{nullptr}, m_width{0}, m_height{0}, m_BPP{0} {
    // Flip the texture upside down, OpenGL expects the pixels to start bottom left (not top left).
    stbi_set_flip_vertically_on_load(1);

    // Desired channels RGBA: 4
    this->m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_BPP, 4);

    glGenTextures(1, &this->m_rendererID);
    glBindTexture(GL_TEXTURE_2D, this->m_rendererID);

    // !!! Must be specified !!!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Scale up settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Horizontal wrap settings, clamp: not extend the area
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Vertical wrap settings, clamp: not extend the area


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);


    // Cleanup image on CPU
    if (this->m_localBuffer) {
        stbi_image_free(this->m_localBuffer);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &this->m_rendererID);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->m_rendererID);
}

void Texture::unBind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
