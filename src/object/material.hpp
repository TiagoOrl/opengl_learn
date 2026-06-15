#ifndef H_STRUCT_LIGHTMAT
#define H_STRUCT_LIGHTMAT

#include <glm/glm.hpp>


struct _material {
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
};


typedef struct _material Material;


#endif