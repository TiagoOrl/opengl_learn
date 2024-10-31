#include "VAO.hpp"




VAO::VAO(
    float vertices[], 
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawType);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(colorOffset * sizeof(float)));
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(textureOffset * sizeof(float)));
    glEnableVertexAttribArray(2); 

}


void VAO::bind() {
    glBindVertexArray(VAOId);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void VAO::unbind() {
    glDeleteVertexArrays(1, &VAOId);
    glDeleteBuffers(1, &VBOId);
}