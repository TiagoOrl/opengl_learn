#ifndef H_CONTROLLER
#define H_CONTROLLER

#include <GLFW/glfw3.h>
#include "../camera/Camera.hpp"



namespace controller {

    void generalInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    }


    void moveCamera(GLFWwindow *window, Camera &camera) {

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


    void changeVisibility(GLFWwindow *window, float &texVisibility) {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            if (texVisibility < 1.0f) 
                texVisibility += 0.001f;
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            if (texVisibility > 0.0f) 
                texVisibility -= 0.001f;
        }
    }
}

#endif