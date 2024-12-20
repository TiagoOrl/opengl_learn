#ifndef H_TEXTURE_CLASS
#define H_TEXTURE_CLASS

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>


class Texture {
    public:
        GLuint ID;
        Texture(const std::string &imgPath, GLint position);
        void bind();
        void activate();

    private:
        GLuint position;
};


#endif