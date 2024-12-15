#ifndef H_CLASS_VBO
#define H_CLASS_VBO


#include <glad/glad.h>

class VBO {
    public:
        VBO(GLuint type);
        void bind();
        void bufferData(GLuint size, float vertices[], int drawType);
        void unbind();

    private:
        GLuint Id;
        GLuint type;

};

#endif