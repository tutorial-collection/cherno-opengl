#ifndef OPENGLTHECHERNO_RGBA_H
#define OPENGLTHECHERNO_RGBA_H

#include <string>
#include <iostream>


class RGBA {
private:
    short m_r;
    short m_g;
    short m_b;
    short m_a;

public:
    RGBA(short r, short g, short b, short a);
    RGBA(float r, float g, float b, float a);

    static short convertTo255(float value1f);
    static float convertTo1f(short value255);


    void print() const {
        std::cout << "rgba(" << this->m_r << ',' << this->m_g << ',' << this->m_b << ',' << this->m_a << ')' << std::endl;
    }


    // Getters
    float getGLR() const { return convertTo1f(this->m_r); };
    float getGLG() const { return convertTo1f(this->m_g); };
    float getGLB() const { return convertTo1f(this->m_b); };
    float getGLA() const { return convertTo1f(this->m_a); };

    short getR() const { return this->m_r; };
    short getG() const { return this->m_g; };
    short getB() const { return this->m_b; };
    short getA() const { return this->m_a; };

    // Setters
    void setR(short r) { this->m_r = r; };
    void setR(float r) {
        this->m_r = RGBA::convertTo255(r);
    };
};


#endif //OPENGLTHECHERNO_RGBA_H
