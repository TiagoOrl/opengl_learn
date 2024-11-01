#include "VAO.hpp"



VAO::VAO(
    float vertices[], 
    GLuint arraySize,
    GLuint vertCount, 
    int drawType, 
    GLsizeiptr stride,
    GLuint colorOffset,
    GLuint textureOffset
    ) {
    verticesCount = vertCount;
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


void VAO::bind(GLuint textId) {
    glBindTexture(GL_TEXTURE_2D, textId);
    glBindVertexArray(VAOId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void VAO::unbind() {
    glDeleteVertexArrays(1, &VAOId);
    glDeleteBuffers(1, &VBOId);
}