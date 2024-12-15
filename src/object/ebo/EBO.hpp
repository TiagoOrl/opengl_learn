#ifndef H_CLASS_EBO
#define H_CLASS_EBO

#include <glad/glad.h>

class EBO {
    public:
        GLuint ID;
        EBO(GLuint indices[], GLuint indicesSize);
        void unbind();
};

#endif