#ifndef OPENGLTHECHERNO_ERROR_H
#define OPENGLTHECHERNO_ERROR_H

#include <iostream>

// Visual Studio Compiler only
#define ASSERT(x, message) if (!(x)) {\
    std::cout << "ASSERTING " << #x << " with message: " << message << std::endl;\
    __debugbreak();\
}

#define STOP(message) \
    std::cout << "STOPPING" << " with message: " << message << std::endl;\
    __debugbreak();\

#endif //OPENGLTHECHERNO_ERROR_H
