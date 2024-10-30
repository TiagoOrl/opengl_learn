#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>

class VAO {
    public:
        GLuint VAOId;
        GLuint VBOId;
        GLuint verticesCount;

        VAO(float * vertices, GLuint vertCount, int drawType, GLuint location, GLuint vertexAttrSize, int type, GLsizeiptr stride);
        void bind();
        void unbind();

};
    

#endif

