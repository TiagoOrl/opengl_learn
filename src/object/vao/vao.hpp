#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "../ebo/ebo.hpp"
#include "../vbo/vbo.hpp"

class VAO {
    public:
        GLuint Id;

        // for 3D objects
        VAO(
            VBO *vbo,
            float vertices[], 
            GLuint arraySize,
            int drawType
        );

        // for light source
        VAO(
            VBO *vbo,
            int drawType
        );
        
        void bind();
        void bindElements();
        void unbind();
        void setVertexAttribute(GLuint location, GLuint size, GLint type, GLsizeiptr stride, GLint offset);

};
    

#endif

