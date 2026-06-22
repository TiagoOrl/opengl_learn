#ifndef H_TIME_NAMESPACE
#define H_TIME_NAMESPACE

#include <GLFW/glfw3.h>


namespace time_utils {
    inline float deltaTime = 0.0f;
    inline float lastFrame = 0.0f;

    inline void calcDeltaTime() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
};


#endif