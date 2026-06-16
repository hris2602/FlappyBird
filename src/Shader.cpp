#include "Shader.h"


void Shader::checkCompileErrors(GLuint shader, const std::string & type) {
    GLint success;
    GLchar info[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info << std::endl;
        } 
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info << std::endl;
        }
    }
}

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    std::string vertexShader;
    std::string fragmentShader;
    std::ifstream vertexSourceFile;
    std::ifstream fragmentSourceFile;

    vertexSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexSourceFile.open(vertexSource);
        fragmentSourceFile.open(fragmentSource);

        if (!vertexSourceFile.is_open() || !fragmentSourceFile.is_open()) {
            std::cout << "ERROR::SHADER::FILE_NOT_FOUND: Check your working directory!" << std::endl;
            return;
        }

        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexSourceFile.rdbuf();
        fragmentStream << fragmentSourceFile.rdbuf();
        vertexSourceFile.close();
        fragmentSourceFile.close();
        vertexShader = vertexStream.str();
        fragmentShader = fragmentStream.str();
    } catch (std::ifstream::failure & e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const GLchar * vertexCode = vertexShader.c_str();
    const GLchar * fragmentCode = fragmentShader.c_str();
    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(program);
}

void Shader::use(){
    glUseProgram(program);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setMat4(const std::string & name, const glm::mat4 & value) const {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec3(const std::string & name, const glm::vec3 & value) const {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}

