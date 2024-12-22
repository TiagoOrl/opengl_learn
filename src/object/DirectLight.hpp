#ifndef H_DIRECT_LIGHT
#define H_DIRECT_LIGHT

#include "shader/Shader.hpp"

#include <glm/glm.hpp>
#include <stdexcept>

class DirectLight {
    public:
        DirectLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
        void setShader(Shader * shader);
        void draw();
        

    private:
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        Shader * shader = NULL;
};


void DirectLight::setShader(Shader * shader){
    this->shader = shader;
}

DirectLight::DirectLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    this->direction = direction;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}


void DirectLight::draw() {
    if (shader == NULL)
        throw std::runtime_error("DirectLight Error(40): DirectLight has no shader");

    shader->use();

    shader->setVec3("dirLight.direction", direction);
    shader->setVec3("dirLight.ambient", ambient);
    shader->setVec3("dirLight.diffuse", diffuse);
    shader->setVec3("dirLight.specular", specular);
}

#endif