// include/Scene.h
#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Mesh.h"

struct Transform {
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f}; // radians
    glm::vec3 scale{1.0f, 1.0f, 1.0f};

    glm::mat4 toMatrix() const;
};

class SceneObject {
public:
    Transform transform;
    std::shared_ptr<Mesh> mesh;
    glm::vec3 baseColor{0.2f, 0.7f, 0.2f};
};

class Scene {
public:
    SceneObject& addObject(const std::shared_ptr<Mesh>& mesh);

    std::vector<SceneObject>& getObjects() { return objects; }

private:
    std::vector<SceneObject> objects;
};
