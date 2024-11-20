#ifndef H_CLASS_CAMERA
#define H_CLASS_CAMERA


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
    public:
        glm::mat4 view;
        glm::mat4 projection;

        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

        float cameraSpeed = 0.014f;

        Camera();
        void createProjection();
        void createView();

        void moveForward();
        void moveBackward();
        void moveRight();
        void moveLeft();
};

#endif