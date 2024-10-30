#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>

class VAO {
    public:
        GLuint VAOId;
        GLuint VBOId;
        GLuint verticesCount;

        VAO(
            float vertices[], 
            unsigned int sizeOf, 
            GLuint vertCount, 
            int drawType, 
            GLuint location, 
            GLuint vertexAttrSize, 
            int type, 
            GLsizeiptr stride,
            GLuint colorLocation,
            GLuint colorOffset
        );
        void bind();
        void unbind();

};
    

#endif

