#ifndef H_CLASS_OBJECT
#define H_CLASS_OBJECT


#include "transform/Transform.hpp"
#include "texture/Texture.hpp"
#include "shader/Shader.hpp"
#include "vao/VAO.hpp"
#include "vbo/VBO.hpp"
#include "../camera/Camera.hpp"
#include "light_material.hpp"

#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <optional>


class Object {
    public:
        Transform *transform = NULL;
        Object(GLFWwindow *window, Shader *shader, float x, float y, float z);
        Object(GLFWwindow *window, Shader *shader, const glm::vec3 &coord);
        void setVerticesData(VBO *vbo, float vertices[], GLuint arraySize, int drawType);
        void setTexture(const std::string imgPath, const std::string &specularPath, GLint position);
        void setShaderUniforms();
        void draw(Camera camera, Object *lightsource);

        glm::vec3 getPosition() const;

        void setLight(LightMaterial light);

        virtual ~Object();

    protected:
        GLFWwindow *window;
        void bindTexture();
        VAO *vao = NULL;
        VBO *vbo = NULL;
        Texture *texture = NULL;
        Texture *specTexture = NULL;

        Shader *shader;
        std::optional<LightMaterial>  light;
};

#endif