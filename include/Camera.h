// include/Camera.h
#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    Camera(float fovDeg, float aspect, float nearPlane, float farPlane);

    void setAspect(float aspect);

    const glm::vec3& getPosition() const { return position; }
    void setPosition(const glm::vec3& p) { position = p; }

    void setTarget(const glm::vec3& t) { target = t; }

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
};
