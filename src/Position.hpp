#ifndef H_POSITION_CLASS
#define H_POSITION_CLASS

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Position {
    public:
        glm::mat4 trans;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        
        Position(GLfloat posX, GLfloat posY);
        void rotate3d();
        void moveHorizontal(GLfloat posX);
        void moveVertical(GLfloat posY);
        void rotate(GLfloat angle);

    private:
        GLfloat posX;
        GLfloat posY;
        GLfloat currentRotZ;
        void translate();
};


#endif