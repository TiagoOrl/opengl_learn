#ifndef H_CONTROLLER
#define H_CONTROLLER

#include <GLFW/glfw3.h>
#include "../camera/Camera.hpp"
#include "../config.hpp"



class Controller {
    public:
        void generalInput(GLFWwindow *window);
        void setCameraMouseInputCallback(GLFWwindow *window, const Camera &_camera);
        void moveCamera(GLFWwindow *window, Camera &camera);
        void mouseRotate(GLFWwindow* window, Camera &camera);
        void changeVisibility(GLFWwindow *window, float &texVisibility);


    private:
        float lastX = SCREEN_WIDTH / 2;
        float lastY = SCREEN_HEIGHT / 2;
        bool firstMouse = true;    
};


void Controller::generalInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    }


void Controller::mouseRotate(GLFWwindow* window, Camera &camera) {
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

    camera.rotate(xoffset, yoffset);
}


void Controller::moveCamera(GLFWwindow *window, Camera &camera) {

    const float cameraSpeed = 0.05f; // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward();

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward();

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft();

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight();
}


void Controller::changeVisibility(GLFWwindow *window, float &texVisibility) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (texVisibility < 1.0f) 
            texVisibility += 0.001f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (texVisibility > 0.0f) 
            texVisibility -= 0.001f;
    }
}

#endif