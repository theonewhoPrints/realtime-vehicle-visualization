// include/Shader.h
#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader() = default;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use() const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& v) const;
    void setFloat(const std::string& name, float value) const;

    unsigned int getId() const { return id; }

private:
    unsigned int id = 0;

    static std::string loadFile(const std::string& path);
    static unsigned int compileShader(unsigned int type, const std::string& source);
};
