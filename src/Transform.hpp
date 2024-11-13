#ifndef H_POSITION_CLASS
#define H_POSITION_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transform {
    public:
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        
        Transform(GLfloat posX, GLfloat posY, GLfloat posZ);
        void apply();
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