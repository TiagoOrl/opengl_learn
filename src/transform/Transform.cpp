#include "Transform.hpp"




Transform::Transform(GLfloat posX, GLfloat posY, GLfloat posZ) {
    this->angle = 0.0f;
    position = glm::vec3(posX, posY, posZ);
    applyTransform(position);

}

void Transform::listenInputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        position.x += speed * time_utils::deltaTime;

    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        position.x -= speed * time_utils::deltaTime;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
        position.z += speed * time_utils::deltaTime;

    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
        position.z -= speed * time_utils::deltaTime;

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        position.y -= speed * time_utils::deltaTime;

    else if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        position.y += speed * time_utils::deltaTime;

    

    applyTransform(position);
}



void Transform::changeAngle(GLfloat angle) {
    this->angle += angle;
}

void Transform::scale(const glm::vec3 &scaling) {
    model = glm::scale(model, scaling);
}


void Transform::applyTransform() {
    model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
}


void Transform::applyTransform(const glm::vec3 &coord) {
    model = glm::mat4(1.0f);

    model = glm::translate(model, coord);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
}