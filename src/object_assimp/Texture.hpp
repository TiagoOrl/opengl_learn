#ifndef H_STRUCT_TEXTURE
#define H_STRUCT_TEXTURE

#include <string>
#include <assimp/Importer.hpp>

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};



#endif