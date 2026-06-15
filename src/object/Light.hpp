#ifndef H_CLASS_LIGHT
#define H_CLASS_LIGHT

#include "Object.hpp"

class Light : public Object {
    public:
        Light(GLFWwindow *window, Camera *camera, Shader *shader, float x, float y, float z);
        Light(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &pos);
        void draw();
};


Light::Light(GLFWwindow *window, Camera *camera, Shader *shader, float x, float y, float z) 
:Object(window, camera, shader, x, y, z) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
}


Light::Light(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &pos) 
    :Object(window, camera, shader, pos)
{
    this->vbo = new VBO(GL_ARRAY_BUFFER);
}


void Light::draw() {
    shader->use();
    
    shader->setVec3("diffuse", &glm::vec3(1.0f)[0]);

    shader->setProjection(camera->projection, std::string("projection"));
    shader->setView(camera->view, std::string("view"));

    transform->update();

    shader->setModel(transform->model, std::string("model"));


    vao->bind();
}

#endif