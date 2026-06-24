#include "./transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../time/time.hpp"


Transform::Transform() {
    angle = 0.0f;
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    update();
}


Transform::Transform(GLfloat posX, GLfloat posY, GLfloat posZ) {
    this->angle = 0.0f;
    position = glm::vec3(posX, posY, posZ);
    update();
}

void Transform::addX() {
    position.x += speed * time_utils::deltaTime;
    update();
}


void Transform::decX() {
    position.x -= speed * time_utils::deltaTime;
    update();
}

void Transform::addY() {
    position.y += speed * time_utils::deltaTime;
    update();
}

void Transform::decY() {
    position.y -= speed * time_utils::deltaTime;
    update();
}

void Transform::addZ() {
    position.z += speed * time_utils::deltaTime;
    update();
}

void Transform::decZ() {
    position.z -= speed * time_utils::deltaTime;
    update();
}


void Transform::incrementAngle(GLfloat angle) {
    this->angle += angle * time_utils::deltaTime * speed;
    update();
}


void Transform::incrementScale(GLfloat scale) {
    this->scale += scale * time_utils::deltaTime * speed;
    if (this->scale < 0)
        this->scale = 0;
    update();
}


void Transform::changeAngle(GLfloat angle) {
    this->angle = angle;
    update();
}


void Transform::changeScale(GLfloat scale) {
    if (scale < 0)
        return;
    this->scale = scale;
    update();
}


void Transform::update() {
    model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.6f, 0.0f));
}