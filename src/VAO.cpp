#include "VAO.hpp"




VAO::VAO(float vertices[], unsigned int sizeOf, GLuint vertCount, int drawType, GLuint location, GLuint vertexAttrSize, int type, GLsizeiptr stride) {
    verticesCount = vertCount;
    glGenVertexArrays(1, &VAOId);
    glGenBuffers(1, &VBOId);

    glBindVertexArray(VAOId);
    glBindBuffer(GL_ARRAY_BUFFER, VBOId);
    glBufferData(GL_ARRAY_BUFFER, sizeOf, vertices, drawType);
    glVertexAttribPointer(location, vertexAttrSize, type, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}


void VAO::bind() {
    glBindVertexArray(VAOId);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void VAO::unbind() {
    glDeleteVertexArrays(1, &VAOId);
    glDeleteBuffers(1, &VBOId);
}