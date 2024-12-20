
#include "Camera.hpp"
#include <iostream>


Camera::Camera(const glm::vec3 initialPos) {
    position = initialPos;
}


void Camera::lookAt() {
    view = glm::lookAt(
            position, 
            position + front, 
            up
        );
}


void Camera::createProjection() {
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}



void Camera::moveForward() {
    position += cameraSpeed * front * time_utils::deltaTime;
}


void Camera::moveBackward() {
    position -= cameraSpeed * front * time_utils::deltaTime;
}


void Camera::moveRight() {
    position += glm::normalize(glm::cross(front, up)) * cameraSpeed * time_utils::deltaTime;
}


void Camera::moveLeft() {
    position -= glm::normalize(glm::cross(front, up)) * cameraSpeed * time_utils::deltaTime;
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

    front = glm::normalize(direction);
}


void Camera::listenInputs(GLFWwindow *window) {
    moveCamera(window);
    rotateCamera(window);
}


void Camera::moveCamera(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed = config::MOVE_FAST;
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        cameraSpeed = config::MOVE_SLOW;


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveForward();

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveBackward();

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveLeft();

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveRight();
}


void Camera::rotateCamera(GLFWwindow *window) {
    double xpos;
    double ypos;

    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    rotate(xoffset, yoffset);
}