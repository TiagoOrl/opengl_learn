#ifndef H_CLASS_MESH
#define H_CLASS_MESH

#include <vector>
#include "Vertex.hpp"
#include "Texture.hpp"
#include "../object/shader/Shader.hpp"


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