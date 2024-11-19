#include "Camera.hpp"


Camera::Camera() {
}


void Camera::createView() {
    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    
    view = glm::lookAt(
            glm::vec3(camX, 0.0, camZ), 
            glm::vec3(0.0, 0.0, 0.0), 
            glm::vec3(0.0, 1.0, 0.0)
        );
}


void Camera::createProjection() {
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}