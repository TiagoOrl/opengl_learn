
#include "Camera.hpp"
#include <iostream>


Camera::Camera() {
}


void Camera::createView() {
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
    cameraPos += cameraSpeed * cameraFront * time_utils::deltaTime;
}


void Camera::moveBackward() {
    cameraPos -= cameraSpeed * cameraFront * time_utils::deltaTime;
}


void Camera::moveRight() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * time_utils::deltaTime;
}


void Camera::moveLeft() {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * time_utils::deltaTime;
}


void Camera::rotate(double xoffset, double yoffset) {
    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
}