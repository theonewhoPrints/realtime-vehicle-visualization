// src/Scene.cpp
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::toMatrix() const {
    glm::mat4 M(1.0f);
    M = glm::translate(M, position);
    M = glm::rotate(M, rotation.x, glm::vec3(1, 0, 0));
    M = glm::rotate(M, rotation.y, glm::vec3(0, 1, 0));
    M = glm::rotate(M, rotation.z, glm::vec3(0, 0, 1));
    M = glm::scale(M, scale);
    return M;
}

SceneObject& Scene::addObject(const std::shared_ptr<Mesh>& mesh) {
    SceneObject obj;
    obj.mesh = mesh;
    objects.push_back(obj);
    return objects.back();
}
