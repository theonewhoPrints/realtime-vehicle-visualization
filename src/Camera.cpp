// src/Camera.cpp
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fovDeg, float aspect_, float nearP, float farP)
    : position(0.0f, 3.0f, 8.0f),
      target(0.0f, 0.0f, 0.0f),
      up(0.0f, 1.0f, 0.0f),
      fov(fovDeg),
      aspect(aspect_),
      nearPlane(nearP),
      farPlane(farP) {}

void Camera::setAspect(float aspect_) {
    aspect = aspect_;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}
