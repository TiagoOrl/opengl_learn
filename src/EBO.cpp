#include "EBO.hpp"




EBO::EBO(GLuint indices[], GLuint indicesSize) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
}


void EBO::unbind() {
    glDeleteBuffers(1, &ID);
}