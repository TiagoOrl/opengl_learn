#include "VAO.hpp"



// for 3D 
VAO::VAO(
    VBO vbo,
    float vertices[], 
    GLuint arraySize,
    int drawType
) {
    glGenVertexArrays(1, &Id);
    glBindVertexArray(Id);

    vbo.bind();
    vbo.bufferData(arraySize, vertices, drawType);
}


// for light source
VAO::VAO(VBO vbo, int drawType) {
    glGenVertexArrays(1, &Id);
    glBindVertexArray(Id);

    vbo.bind();
}


void VAO::setVertexAttribute(GLuint location, GLuint size, GLint type, GLsizeiptr stride, GLint offset) {
    glVertexAttribPointer(location, size, type, GL_FALSE, stride, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(location);
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

