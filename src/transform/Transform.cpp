#include "Transform.hpp"




Transform::Transform(GLfloat posX, GLfloat posY, GLfloat posZ) {
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->angle = 0.0f;

    applyTransform(glm::vec3(posX, posY, posZ));

}

void Transform::listenInputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        this->posX += speed * time_utils::deltaTime;

    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        this->posX -= speed * time_utils::deltaTime;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
        this->posZ += speed * time_utils::deltaTime;

    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
        this->posZ -= speed * time_utils::deltaTime;

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        this->posY -= speed * time_utils::deltaTime;

    else if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        this->posY += speed * time_utils::deltaTime;

    


    applyTransform(glm::vec3(posX, posY, posZ));
}


void Transform::moveVertical(GLfloat posY) {
    this->posY += posY;
}


void Transform::moveHorizontal(GLfloat posX) {
    this->posX += posX;
}


void Transform::moveZ(GLfloat posZ) {
    this->posZ += posZ;
}


void Transform::changeAngle(GLfloat angle) {
    this->angle += angle;
}

void Transform::scale(const glm::vec3 &scaling) {
    model = glm::scale(model, scaling);
}


void Transform::applyTransform(const glm::vec3 &coord) {
    model = glm::mat4(1.0f);

    model = glm::translate(model, coord);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
}