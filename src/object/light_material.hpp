#ifndef H_STRUCT_LIGHTMAT
#define H_STRUCT_LIGHTMAT

#include <glm/glm.hpp>


struct _lightmaterial {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
};


typedef struct _lightmaterial LightMaterial;


#endif