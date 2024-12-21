#ifndef H_CLASS_LIGHT
#define H_CLASS_LIGHT

#include "Object.hpp"

class Light : public Object {
    public:
        Light(GLFWwindow *window, float x, float y, float z);
        Light(GLFWwindow *window, const glm::vec3 &pos);
        void draw(Camera camera);
};


Light::Light(GLFWwindow *window, float x, float y, float z) 
    :Object(window, x, y, z) {
        
    }


Light::Light(GLFWwindow *window, const glm::vec3 &pos) 
    :Object(window, pos)
{

}


void Light::draw(Camera camera) {
    shader->use();
    
    shader->setVec3("diffuse", glm::vec3(1.0f));

    shader->setProjection(camera.projection, std::string("projection"));
    shader->setView(camera.view, std::string("view"));

    transform->update();

    shader->setModel(transform->model, std::string("model"));


    vao->bind();
}

#endif