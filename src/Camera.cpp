#include "Camera.hpp"


Camera::Camera() {
    cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
}


void Camera::createView() {
    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    
    view = glm::lookAt(
            cameraPos, 
            cameraPos + cameraFront, 
            cameraUp
        );
}


void Camera::createProjection() {
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}



void Camera::moveForward() {
    cameraPos += cameraSpeed * cameraFront;
}


void Camera::moveBackward() {
    cameraPos -= cameraSpeed * cameraFront;
}


void Camera::moveRight() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


void Camera::moveLeft() {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}