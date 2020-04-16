#ifndef OPENGLTHECHERNO_SHADER_H
#define OPENGLTHECHERNO_SHADER_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>


struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader {
private:
    unsigned int m_rendererID;
    std::string m_filePath;
    std::unordered_map<std::string, int> m_locationCache;

    // Uniform
    int getUniformLocation(const std::string &name);

    // Shader create, parse and compiler
    ShaderProgramSource parseShader(const std::string &filePath);
    unsigned int compileShader(unsigned int type, const std::string &shader);
    unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

public:
    Shader(const std::string &filePath);
    ~Shader();

    void bind() const;
    void unBind() const;

    // Set uniforms
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void setUniform1i(const std::string &name, int value);
};


#endif //OPENGLTHECHERNO_SHADER_H
