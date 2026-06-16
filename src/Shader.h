#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader {
    private:
        GLuint program;
        void checkCompileErrors(GLuint shader, const std::string & type);
    public:
        Shader() {}
        Shader(const char* vertexSource, const char* fragmentSource);
        ~Shader();
        void use();
        void setInt(const std::string & name, int value) const;
        void setMat4(const std::string & name, const glm::mat4 & value) const;
        void setVec3(const std::string & name, const glm::vec3 & value) const;
};

#endif