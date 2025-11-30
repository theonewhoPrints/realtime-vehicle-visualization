// include/Mesh.h
#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<unsigned int>& indices);

    void draw(const Shader& shader) const;

private:
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
    unsigned int indexCount = 0;

    void setup(const std::vector<Vertex>& vertices,
               const std::vector<unsigned int>& indices);
};
