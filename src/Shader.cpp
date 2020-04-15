#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


Shader::Shader(const std::string &filePath)
: m_filePath{filePath}, m_rendererID{0} {
    ShaderProgramSource shaderSource = this->parseShader(filePath);
    this->m_rendererID = this->createShader(shaderSource.VertexSource, shaderSource.FragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(this->m_rendererID);
}

int Shader::getUniformLocation(const std::string &name){
    int location =  glGetUniformLocation(this->m_rendererID, name.c_str());

    if (location == -1) {
        std::cout << "@Shader.cpp: WARNING: Uniform " << name << " doesn't exist.";
    }

    return location;
}

void Shader::bind() const {
    glUseProgram(this->m_rendererID);
}

void Shader::unBind() const {
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    int location = this->getUniformLocation(name);
    glUniform4f(location, v0, v1, v2, v3);
}


/**
 * Create a shader
 * @param vertexShader
 * @param fragmentShader
 * @return
 */
unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader) {

    unsigned int program{glCreateProgram()};
    unsigned int vShader{this->compileShader(GL_VERTEX_SHADER, vertexShader)};
    unsigned int fShader{this->compileShader(GL_FRAGMENT_SHADER, fragmentShader)};

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glValidateProgram(program);

    // Delete the shaders, you can do this because they are now linked into a program.
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}


/**
 * Parse a shader
 * @param filePath
 * @return
 */
ShaderProgramSource Shader::parseShader(const std::string &filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        // If is is a shader define
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int) type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}


/**
 * Compile a shader.
 * @param type
 * @param shader
 * @return
 */
unsigned int Shader::compileShader(unsigned int type, const std::string &shader) {
    unsigned int shaderId = glCreateShader(type);
    const char *shaderCString = shader.c_str();

    glShaderSource(shaderId, 1, &shaderCString, nullptr);
    glCompileShader(shaderId);

    // Error handling
    int result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(shaderId, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader"
                  << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}
