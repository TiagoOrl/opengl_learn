#ifndef H_STRUCT_LIGHTMAT
#define H_STRUCT_LIGHTMAT

#include <glm/glm.hpp>


struct _lightmaterial {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


typedef struct _lightmaterial LightMaterial;


#endif