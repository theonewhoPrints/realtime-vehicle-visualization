// src/Renderer.cpp
#include "Renderer.h"

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "Mesh.h"

Renderer::Renderer(int w, int h)
    : width(w),
      height(h),
      camera(60.0f, (float)w / (float)h, 0.1f, 100.0f),
      lightPos(5.0f, 10.0f, 5.0f) {}

std::shared_ptr<Mesh> Renderer::createCubeMesh() {
    // Very simple cube data: positions + normals.
    std::vector<Vertex> vertices = {
        // positions            // normals
        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}},
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}},
        {{-0.5f,  0.5f, -0.5f}, {0, 0, -1}},

        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}},
        {{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}},
        {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}},

        {{-0.5f,  0.5f,  0.5f}, {0, 1, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 1, 0}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}},

        {{-0.5f, -0.5f,  0.5f}, {0, -1, 0}},
        {{ 0.5f, -0.5f,  0.5f}, {0, -1, 0}},
        {{ 0.5f, -0.5f, -0.5f}, {0, -1, 0}},
        {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}},

        {{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}},
        {{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}},
        {{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}},
        {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}},

        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 0, 0}},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,       // front
        4, 5, 6, 6, 7, 4,       // back
        8, 9,10,10,11, 8,       // top
        12,13,14,14,15,12,      // bottom
        16,17,18,18,19,16,      // left
        20,21,22,22,23,20       // right
    };

    return std::make_shared<Mesh>(vertices, indices);
}

void Renderer::initScene() {
    cubeMesh = createCubeMesh();

    // Ego car
    {
        auto& car = scene.addObject(cubeMesh);
        car.transform.position = {0.0f, 0.5f, 0.0f};
        car.transform.scale = {1.0f, 0.5f, 2.0f};
        car.baseColor = {0.2f, 0.7f, 0.3f};
    }

    // Road as a big stretched cube
    {
        auto& road = scene.addObject(cubeMesh);
        road.transform.position = {0.0f, -0.5f, 0.0f};
        road.transform.scale = {5.0f, 0.1f, 50.0f};
        road.baseColor = {0.1f, 0.1f, 0.1f};
    }

    // Another car ahead
    {
        auto& other = scene.addObject(cubeMesh);
        other.transform.position = {0.0f, 0.5f, -10.0f};
        other.transform.scale = {1.0f, 0.5f, 2.0f};
        other.baseColor = {0.8f, 0.1f, 0.1f};
    }
}

void Renderer::init() {
    shader = Shader("shaders/basic.vert", "shaders/basic.frag");

    camera.setPosition(glm::vec3(0.0f, 4.0f, 12.0f));

    initScene();
}

void Renderer::update(float dt) {
    timeAccum += dt;

    // Simple fake motion: move the ego car forward in -Z
    auto& objects = scene.getObjects();

    // ego: index 0, road: 1, other car: 2 (based on initScene)
    if (objects.size() >= 3) {
        float speed = 5.0f; // units per second

        // move road and other car in +Z to simulate ego moving forward
        objects[1].transform.position.z += speed * dt; // road
        objects[2].transform.position.z += speed * dt; // other car

        // wiggle other car sideways (like lane deviation)
        objects[2].transform.position.x = 1.0f * sinf(timeAccum * 0.5f);
    }
}

void Renderer::render() {
    glViewport(0, 0, width, height);
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = camera.getProjectionMatrix();

    shader.setMat4("uView", view);
    shader.setMat4("uProj", proj);
    shader.setVec3("uCameraPos", camera.getPosition());
    shader.setVec3("uLightPos", lightPos);

    for (auto& obj : scene.getObjects()) {
        glm::mat4 model = obj.transform.toMatrix();
        shader.setMat4("uModel", model);
        shader.setVec3("uBaseColor", obj.baseColor);

        if (obj.mesh) {
            obj.mesh->draw(shader);
        }
    }
}
