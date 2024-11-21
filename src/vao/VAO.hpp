#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "../ebo/EBO.hpp"

class VAO {
    public:
        GLuint VAOId;
        GLuint VBOId;

        VAO(
            float vertices[], 
            GLuint arraySize,
            int drawType, 
            GLsizeiptr stride,
            GLuint colorOffset,
            GLuint textureOffset
        );

        VAO(
            float vertices[], 
            GLuint arraySize,
            int drawType, 
            GLsizeiptr stride,
            GLuint textureOffset
        );
        
        void bind();
        void bindElements();
        void unbind();

    private:
        void setVertexAttribute(GLuint index, GLuint size, GLint type, GLsizeiptr stride, GLint offset);

};
    

#endif

