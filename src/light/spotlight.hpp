#ifndef H_CLASS_SPOTLIGHT
#define H_CLASS_SPOTLIGHT


#include "../shader/shader.hpp"
#include "../camera/camera.hpp"

#include <glm/glm.hpp>

class Spotlight {

public:
    Spotlight(
        Shader *shader, 
        Camera *camera, 
        float cutoff, float outerCutoff, 
        glm::vec3 diffuse, 
        glm::vec3 specular, 
        GLfloat constant, GLfloat linear, GLfloat quadratic)
        : 
            diffuse(diffuse), 
            specular(specular), 
            shader(shader), 
            camera(camera), 
            constant(constant), 
            linear(linear), 
            quadratic(quadratic) {

        this->cutoff = glm::cos(glm::radians(cutoff));
        this->outerCutoff = glm::cos(glm::radians(outerCutoff));

    }


    float getCutoff() const {
        return cutoff;
    }


    void draw() {
        shader->use();
        shader->setVec3("spotlight.position",  &camera->position[0]);
        shader->setVec3("spotlight.direction", &camera->front[0]);
        shader->setFloat("spotlight.cutoff",   cutoff);
        shader->setFloat("spotlight.outerCutoff", outerCutoff);
        shader->setFloat("spotlight.constant", constant);
        shader->setFloat("spotlight.linear", linear);
        shader->setFloat("spotlight.quadratic", quadratic);


        shader->setVec3("spotlight.diffuse", &diffuse[0]);
        shader->setVec3("spotlight.specular", &specular[0]);
    }

    
private:
    Shader *shader = NULL;
    Camera *camera = NULL;
    float cutoff;
    float outerCutoff;
    float constant;
    float linear;
    float quadratic;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif