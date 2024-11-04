#include "Texture.hpp"




Texture::Texture(const std::string &imgPath, GLint type, GLint position) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        this->position = position;
        glGenTextures(1, &ID);
        this->bind();
        
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }


    stbi_image_free(data);
}


void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}


void Texture::activate() {
    glActiveTexture(this->position);
}