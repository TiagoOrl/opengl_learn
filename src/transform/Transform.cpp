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

void Transform::scale(const glm::vec3 &scaling) {
    model = glm::scale(model, scaling);
}


void Transform::applyTransform(const glm::vec3 &coord, unsigned int i) {
    model = glm::mat4(1.0f);

    model = glm::translate(model, coord);
    model = glm::rotate(model, glm::radians(angle) * (i + 1), glm::vec3(1.0f, 0.3f, 0.5f));
}