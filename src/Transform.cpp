#include "Transform.hpp"




Transform::Transform(GLfloat posX, GLfloat posY, GLfloat posZ) {
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->angle = 0.0f;

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


void Transform::apply() {
    model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.77f, 0.3f));
    view  = glm::translate(view, glm::vec3(posX, posY, posZ));
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}
