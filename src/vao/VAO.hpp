#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "../ebo/EBO.hpp"
#include "../vbo/VBO.hpp"

class VAO {
    public:
        GLuint Id;

        VAO(
            VBO vbo,
            float vertices[], 
            GLuint arraySize,
            int drawType, 
            GLsizeiptr stride,
            GLuint colorOffset,
            GLuint textureOffset
        );

        // for 3D objects
        VAO(
            VBO vbo,
            float vertices[], 
            GLuint arraySize,
            int drawType, 
            GLsizeiptr stride,
            GLuint textureOffset
        );

        // for lighting source
        VAO(
            int drawType, 
            GLsizeiptr stride
        );
        
        void bind();
        void bindElements();
        void unbind();

    private:
        void setVertexAttribute(GLuint index, GLuint size, GLint type, GLsizeiptr stride, GLint offset);

};
    

#endif

