// include/Renderer.h
#pragma once
#include <memory>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Scene.h"

class Renderer {
public:
    Renderer(int width, int height);

    void init();
    void update(float dt);
    void render();

private:
    int width;
    int height;

    Camera camera;
    Shader shader;
    Scene scene;

    glm::vec3 lightPos;
    float timeAccum = 0.0f;

    std::shared_ptr<Mesh> cubeMesh;

    void initScene();
    std::shared_ptr<Mesh> createCubeMesh();
};
