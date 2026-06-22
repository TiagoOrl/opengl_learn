#ifndef H_MODEL_ASSIMP
#define H_MODEL_ASSIMP

#include "./model.hpp"



void Model::draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);
} 



#endif