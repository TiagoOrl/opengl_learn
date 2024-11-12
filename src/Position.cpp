#include "Position.hpp"




Transform::Transform(GLfloat posX, GLfloat posY) {
    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(posX, posY, 1.0f));

    this->posX = posX;
    this->posY = posY;
    this->currentRotZ = 0.0f;

    this->rotate(currentRotZ);
}


void Transform::moveVertical(GLfloat posY) {
    this->posY += posY;
    translate();
}


void Transform::moveHorizontal(GLfloat posX) {
    this->posX += posX;
    translate();
}


void Transform::apply() {
    model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.77f, 0.3f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}


void Transform::rotate(GLfloat amount) {
    this->currentRotZ += amount;
    trans = glm::rotate(trans, amount, glm::vec3(0.0f, 0.0f, 1.0f));
    
}


void Transform::translate() {
    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(this->posX, this->posY, 1.0f));

    trans = glm::rotate(trans, this->currentRotZ, glm::vec3(0.0f, 0.0f, 1.0f));
}