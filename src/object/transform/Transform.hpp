#ifndef H_POSITION_CLASS
#define H_POSITION_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../time/Time.hpp"


class Transform {
    public:
        glm::mat4 model;
        glm::vec3 position;
        

        Transform(GLfloat posX, GLfloat posY, GLfloat posZ);

        void update();
        void applyTransform(const glm::vec3 &coord);
        void listenInputs(GLFWwindow *window);
        void incrementAngle(GLfloat angle);
        void incrementScale(GLfloat scale);

        void changeAngle(GLfloat angle);
        void changeScale(GLfloat scale);

    private:
        float scale = 1.0f;
        float scaleAmount = 0.4f;
        bool inControl = false;

        GLfloat speed = 3.2f;
        GLfloat angle = 0.0f;
};


#endif