#ifndef H_STRUCT_VERTEX
#define H_STRUCT_VERTEX

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};



#endif