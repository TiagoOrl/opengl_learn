#include "VAO.hpp"



VAO::VAO(
    VBO vbo,
    float vertices[], 
    GLuint arraySize,
    int drawType, 
    GLsizeiptr stride,
    GLuint colorOffset,
    GLuint textureOffset
) {
    glGenVertexArrays(1, &Id);
    glBindVertexArray(Id);

    vbo.bind();
    vbo.bufferData(arraySize, vertices, drawType);

    setVertexAttribute(0, 3, GL_FLOAT, stride, 0);
    setVertexAttribute(1, 3, GL_FLOAT, stride, colorOffset);
    setVertexAttribute(2, 2, GL_FLOAT, stride, textureOffset);
}

// for 3D 
VAO::VAO(
    VBO vbo,
    float vertices[], 
    GLuint arraySize,
    int drawType, 
    GLsizeiptr stride,
    GLuint textureOffset
) {
    glGenVertexArrays(1, &Id);
    glBindVertexArray(Id);

    vbo.bind();
    vbo.bufferData(arraySize, vertices, drawType);

    setVertexAttribute(0, 3, GL_FLOAT, stride, 0);
    setVertexAttribute(1, 2, GL_FLOAT, stride, textureOffset);
}


// for light source
VAO::VAO(VBO vbo, int drawType, GLsizeiptr stride) {
    glGenVertexArrays(1, &Id);
    glBindVertexArray(Id);

    vbo.bind();

    setVertexAttribute(0, 3, GL_FLOAT, stride, 0);
}


void VAO::setVertexAttribute(GLuint index, GLuint size, GLint type, GLsizeiptr stride, GLint offset) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)(offset * sizeof(type)));
    glEnableVertexAttribArray(index);
}


void VAO::bind() {
    glBindVertexArray(Id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void VAO::bindElements() {
    glBindVertexArray(Id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void VAO::unbind() {
    glDeleteVertexArrays(1, &Id);
}

