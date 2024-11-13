#include "VAO.hpp"



VAO::VAO(
    float vertices[], 
    GLuint arraySize,
    int drawType, 
    GLsizeiptr stride,
    GLuint colorOffset,
    GLuint textureOffset
) {
    glGenVertexArrays(1, &VAOId);
    glGenBuffers(1, &VBOId);

    glBindVertexArray(VAOId);
    glBindBuffer(GL_ARRAY_BUFFER, VBOId);
    glBufferData(GL_ARRAY_BUFFER, arraySize, vertices, drawType);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(colorOffset * sizeof(float)));
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(textureOffset * sizeof(float)));
    glEnableVertexAttribArray(2); 

}

// for 3D 
VAO::VAO(
    float vertices[], 
    GLuint arraySize,
    int drawType, 
    GLsizeiptr stride,
    GLuint textureOffset
) {
    glGenVertexArrays(1, &VAOId);
    glGenBuffers(1, &VBOId);

    glBindVertexArray(VAOId);
    glBindBuffer(GL_ARRAY_BUFFER, VBOId);
    glBufferData(GL_ARRAY_BUFFER, arraySize, vertices, drawType);

    setVertexAttribute(0, 3, GL_FLOAT, stride, 0);
    setVertexAttribute(1, 2, GL_FLOAT, stride, textureOffset);
}


void VAO::setVertexAttribute(GLuint index, GLuint size, GLint type, GLsizeiptr stride, GLint offset) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)(offset * sizeof(type)));
    glEnableVertexAttribArray(index);
}


void VAO::bind() {
    glBindVertexArray(VAOId);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void VAO::bindElements() {
    glBindVertexArray(VAOId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void VAO::unbind() {
    glDeleteVertexArrays(1, &VAOId);
    glDeleteBuffers(1, &VBOId);
}

