#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "EBO.hpp"

class VAO {
    public:
        GLuint VAOId;
        GLuint VBOId;
        GLuint verticesCount;

        VAO(
            float vertices[], 
            GLuint arraySize,
            GLuint vertCount, 
            int drawType, 
            GLsizeiptr stride,
            GLuint colorOffset,
            GLuint textureOffset
        );

        void bind();
        void unbind();

};
    

#endif

