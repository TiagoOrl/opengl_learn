#ifndef H_POSITION_CLASS
#define H_POSITION_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../time/Time.hpp"


class Transform {
    public:
        glm::mat4 model;
        glm::vec3 position;

        Transform(GLfloat posX, GLfloat posY, GLfloat posZ);

        void applyTransform();
        void applyTransform(const glm::vec3 &coord);
        void scale(const glm::vec3 &scaling);
        void listenInputs(GLFWwindow *window);

    private:
        GLfloat speed = 3.2f;
        GLfloat angle;

        void changeAngle(GLfloat angle);
};


#endif