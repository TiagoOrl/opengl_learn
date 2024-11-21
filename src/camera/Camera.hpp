#ifndef H_CLASS_CAMERA
#define H_CLASS_CAMERA


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../time/Time.hpp"


class Camera {
    public:
        glm::mat4 view;
        glm::mat4 projection;
        
        Camera();

        void createProjection();
        void createView();

        void moveForward();
        void moveBackward();
        void moveRight();
        void moveLeft();
        void rotate(double xoffset, double yoffset);

    private:
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

        float cameraSpeed = 2.34f;
        float yaw = -90.0f;
        float pitch = 0.0f;
};

#endif