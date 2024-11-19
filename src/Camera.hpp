#ifndef H_CLASS_CAMERA
#define H_CLASS_CAMERA


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
    public:
        glm::mat4 view;
        glm::mat4 projection;

        Camera();
        void createProjection();
        void createView();
};

#endif