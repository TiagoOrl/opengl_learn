#ifndef H_MESH_ASSIMP
#define H_MESH_ASSIMP

#include <vector>
#include "./vertex.hpp"
#include "./texture_model.hpp"
#include "../shader/shader.hpp"


class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;


        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader);

    private:
        unsigned int VAO, VBO, EBO;
        void setupMesh();
    

};

#endif