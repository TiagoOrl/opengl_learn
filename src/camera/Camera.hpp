#ifndef H_CLASS_CAMERA
#define H_CLASS_CAMERA


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../time/Time.hpp"
#include "../config.hpp"


class Camera {
    public:
        glm::mat4 view;
        glm::mat4 projection;
        
        Camera(const glm::vec3 initialPos);

        void createProjection();
        void createView();

        void moveForward();
        void moveBackward();
        void moveRight();
        void moveLeft();
        void rotate(double xoffset, double yoffset);

        void listenInputs(GLFWwindow *window);
        


    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

        float cameraSpeed = config::MOVE_SLOW;
        float yaw = 90.0f;
        float pitch = 0.0f;

        float lastX = config::SCREEN_WIDTH / 2;
        float lastY = config::SCREEN_HEIGHT / 2;
        bool firstMouse = true;    

        void moveCamera(GLFWwindow *window);
        void rotateCamera(GLFWwindow *window);
};

#endif