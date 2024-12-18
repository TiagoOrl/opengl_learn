#ifndef H_CLASS_SPOTLIGHT
#define H_CLASS_SPOTLIGHT


#include "shader/Shader.hpp"
#include "../camera/Camera.hpp"

#include <glm/glm.hpp>

class Spotlight {

    public:
        Spotlight(float cutoff) {
            this->cutoff = glm::cos(glm::radians(cutoff));
        }


        float getCutoff() const {
            return cutoff;
        }


        void draw(Camera camera, Shader *shader) {
            shader->use();
            shader->setVec3("spotlight.position",  camera.position);
            shader->setVec3("spotlight.direction", camera.front);
            shader->setFloat("spotlight.cutoff",   cutoff);
        }

        
    private:
        float cutoff;
};

#endif