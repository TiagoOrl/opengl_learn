#ifndef H_CONTROLLER
#define H_CONTROLLER

#include <GLFW/glfw3.h>
#include "../camera/Camera.hpp"
#include "../config.hpp"



class Controller {
    public:
        void listenInputs(GLFWwindow *window, float &visibility);
        
    private:
        void generalInput(GLFWwindow *window);
        void changeVisibility(GLFWwindow *window, float &texVisibility);
};


void Controller::listenInputs(GLFWwindow *window, float &visibility) {
    generalInput(window);
    changeVisibility(window, visibility);
}


void Controller::generalInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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