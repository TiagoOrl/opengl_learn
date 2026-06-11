#ifndef H_CLASS_SPOTLIGHT
#define H_CLASS_SPOTLIGHT


#include "shader/Shader.hpp"
#include "../camera/Camera.hpp"

#include <glm/glm.hpp>

class Spotlight {

    public:
        Spotlight(Shader *shader, float cutoff, float outerCutoff, glm::vec3 diffuse, glm::vec3 specular)
            : diffuse(diffuse), specular(specular), shader(shader) {
            this->cutoff = glm::cos(glm::radians(cutoff));
            this->outerCutoff = glm::cos(glm::radians(outerCutoff));

        }


        float getCutoff() const {
            return cutoff;
        }


        void draw(Camera camera) {
            shader->use();
            shader->setVec3("spotlight.position",  &camera.position[0]);
            shader->setVec3("spotlight.direction", &camera.front[0]);
            shader->setFloat("spotlight.cutoff",   cutoff);
            shader->setFloat("spotlight.outerCutoff", outerCutoff);

            shader->setVec3("spotlight.diffuse", &diffuse[0]);
            shader->setVec3("spotlight.specular", &specular[0]);
        }

        
    private:
        Shader *shader;
        float cutoff;
        float outerCutoff;
        glm::vec3 diffuse;
        glm::vec3 specular;
};

#endif