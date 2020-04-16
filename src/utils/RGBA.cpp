#include "RGBA.h"

RGBA::RGBA(short r, short g, short b, short a)
: m_r{r}, m_g{g}, m_b{b}, m_a{a} {}

RGBA::RGBA(float r, float g, float b, float a) {
    this->m_r = RGBA::convertTo255(r);
    this->m_g = RGBA::convertTo255(g);
    this->m_b = RGBA::convertTo255(b);
    this->m_a = RGBA::convertTo255(a);
}


short RGBA::convertTo255(float value1f) {
    return (short)(value1f * 255.0f);
}

float RGBA::convertTo1f(short value255) {
    return (float)value255 / 255.0f;
}