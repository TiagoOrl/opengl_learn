#ifndef H_CLASS_OBJECT
#define H_CLASS_OBJECT


#include "transform/Transform.hpp"
#include "texture/Texture.hpp"
#include "shader/Shader.hpp"
#include "vao/VAO.hpp"
#include "vbo/VBO.hpp"
#include "../camera/Camera.hpp"
#include "./material.hpp"

#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <optional>


class Object {
    public:
        Transform *transform = NULL;
        Object(GLFWwindow *window, Camera *camera, Shader *shader, float x, float y, float z);
        Object(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &coord);
        void setVerticesData(float vertices[], GLuint arraySize, int drawType);
        void setTexture(const std::string imgPath, const std::string &specularPath, GLint position);
        void setShaderUniforms();
        void draw(Object *lightsource);

        glm::vec3 getPosition() const;

        void setMaterial(Material light);

        virtual ~Object();

    protected:
        GLFWwindow *window;
        void bindTexture();
        VAO *vao = NULL;
        VBO *vbo = NULL;
        Camera *camera = NULL;
        Texture *texture = NULL;
        Texture *specTexture = NULL;

        Shader *shader;
        std::optional<Material>  light;
};

#endif