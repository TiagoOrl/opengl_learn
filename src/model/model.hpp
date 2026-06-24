#ifndef H_CLASS_MODEL
#define H_CLASS_MODEL



#include "./mesh.hpp"
#include "../transform/transform.hpp"
#include "../camera/camera.hpp"
#include <vector>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GLFW/glfw3.h>

class Model 
{
    public:
        Model(GLFWwindow *window, Camera *camera, Shader *shader, const char *path, const glm::vec3 &pos);
        void draw();
        void scale(GLfloat scale);
        glm::vec3 getPosition() const;

    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        bool gammaCorrection;
        Transform *transform = NULL;
        GLFWwindow *window;
        Camera *camera = NULL;
        Shader *shader = NULL;

        void loadModel(std::string path);
        void listenInputs();
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
};


#endif