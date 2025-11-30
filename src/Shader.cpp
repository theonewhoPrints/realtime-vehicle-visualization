// src/Shader.cpp
#include "Shader.h"
#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::string Shader::loadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::string msg = "Shader compile error: ";
        msg += info;
        throw std::runtime_error(msg);
    }
    return shader;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vsSource = loadFile(vertexPath);
    std::string fsSource = loadFile(fragmentPath);

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vsSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fsSource);

    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);

    int success = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char info[512];
        glGetProgramInfoLog(id, 512, nullptr, info);
        std::string msg = "Program link error: ";
        msg += info;
        throw std::runtime_error(msg);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    int loc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& v) const {
    int loc = glGetUniformLocation(id, name.c_str());
    glUniform3fv(loc, 1, &v[0]);
}

void Shader::setFloat(const std::string& name, float value) const {
    int loc = glGetUniformLocation(id, name.c_str());
    glUniform1f(loc, value);
}
