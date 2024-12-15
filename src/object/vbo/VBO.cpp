#include "VBO.hpp"


VBO::VBO(GLuint type) {
    this->type = type;
    glGenBuffers(1, &Id);
}


void VBO::bind() {
    glBindBuffer(this->type, Id);
}


void VBO::bufferData(GLuint size, float vertices[], int drawType) {
    glBufferData(this->type, size, vertices, drawType);
}


void VBO::unbind() {
    glDeleteBuffers(1, &Id);
}