#ifndef H_POSITION_CLASS
#define H_POSITION_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transform {
    public:
        glm::mat4 model;

        Transform(GLfloat posX, GLfloat posY, GLfloat posZ);

        void applyTransform(glm::vec3 &coord, unsigned int i);
        void moveHorizontal(GLfloat posX);
        void moveVertical(GLfloat posY);
        void moveZ(GLfloat posZ);
        void changeAngle(GLfloat angle);

    private:
        GLfloat posX;
        GLfloat posY;
        GLfloat posZ;
        GLfloat angle;
};


#endif