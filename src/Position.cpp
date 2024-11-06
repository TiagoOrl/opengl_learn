#include "Position.hpp"



Position::Position(GLfloat posX, GLfloat posY) {
    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(posX, posY, 1.0f));

    this->posX = posX;
    this->posY = posY;
    this->currentRotZ = 0.0f;

    this->rotate(currentRotZ);
}


void Position::moveVertical(GLfloat posY) {
    this->posY += posY;
    translate();
}


void Position::moveHorizontal(GLfloat posX) {
    this->posX += posX;
    translate();
}


void Position::rotate(GLfloat amount) {
    this->currentRotZ += amount;
    trans = glm::rotate(trans, amount, glm::vec3(0.0f, 0.0f, 1.0f));
    
}


void Position::translate() {
    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(this->posX, this->posY, 1.0f));

    trans = glm::rotate(trans, this->currentRotZ, glm::vec3(0.0f, 0.0f, 1.0f));
}