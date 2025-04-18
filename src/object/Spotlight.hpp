#ifndef H_CLASS_SPOTLIGHT
#define H_CLASS_SPOTLIGHT


#include "shader/Shader.hpp"
#include "../camera/Camera.hpp"

#include <glm/glm.hpp>

class Spotlight {

    public:
        Spotlight(float cutoff, float outerCutoff, glm::vec3 diffuse, glm::vec3 specular)
            : diffuse(diffuse), specular(specular) {
            this->cutoff = glm::cos(glm::radians(cutoff));
            this->outerCutoff = glm::cos(glm::radians(outerCutoff));

        }


        float getCutoff() const {
            return cutoff;
        }


        void draw(Camera camera, Shader *shader) {
            shader->use();
            shader->setVec3("spotlight.position",  camera.position);
            shader->setVec3("spotlight.direction", camera.front);
            shader->setFloat("spotlight.cutoff",   cutoff);
            shader->setFloat("spotlight.outerCutoff", outerCutoff);

            shader->setVec3("spotlight.diffuse", diffuse);
            shader->setVec3("spotlight.specular", specular);
        }

        
    private:
        float cutoff;
        float outerCutoff;
        glm::vec3 diffuse;
        glm::vec3 specular;
};

#endif