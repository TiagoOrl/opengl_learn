#ifndef H_TEXTURE_CLASS
#define H_TEXTURE_CLASS

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>


class Texture {
    public:
        GLuint ID;
        Texture(const std::string &imgPath, GLint type, GLint position);
        void bind();

    private:
        GLuint position;
};


#endif