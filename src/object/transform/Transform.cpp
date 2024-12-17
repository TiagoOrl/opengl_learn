#include "Transform.hpp"


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

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        incrementScale(scaleAmount);

    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        incrementScale(-scaleAmount);

    

    update();
}



void Transform::incrementAngle(GLfloat angle) {
    this->angle += angle * time_utils::deltaTime * speed;
}


void Transform::incrementScale(GLfloat scale) {
    this->scale += scale * time_utils::deltaTime * speed;
    if (this->scale < 0)
        this->scale = 0;
}


void Transform::changeAngle(GLfloat angle) {
    this->angle = angle;
}


void Transform::changeScale(GLfloat scale) {
    if (scale < 0)
        return;
    this->scale = scale;
}


void Transform::update() {
    model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.6f, 0.0f));
}