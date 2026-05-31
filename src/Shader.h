#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>


class Shader {
    private:
        GLuint shader;
        void checkCompileErrors(GLuint shader, const std::string & type);
    public:
        Shader() {}
        Shader(const char* vertexSource, const char* fragmentSource);
        ~Shader();
        void use();
};

#endif