#ifndef H_CLASS_OBJECT
#define H_CLASS_OBJECT


#include "transform/transform.hpp"
#include "texture/texture.hpp"
#include "shader/shader.hpp"
#include "vao/vao.hpp"
#include "vbo/vbo.hpp"
#include "../camera/camera.hpp"
#include <GLFW/glfw3.h>
#include <vector>

#include <optional>


class Object {
    public:
        Object(GLFWwindow *window, Camera *camera, Shader *shader, float x, float y, float z);
        Object(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &coord);
        void setVerticesData(float vertices[], GLuint arraySize, int drawType);
        void setTexture(const std::string imgPath, const std::string &specularPath, GLint position);
        void draw();
        void scale(GLfloat scale);
        glm::vec3 getPosition() const;

        virtual ~Object();

    protected:
        Transform *transform = NULL;
        GLFWwindow *window;
        VAO *vao = NULL;
        VBO *vbo = NULL;
        Camera *camera = NULL;
        Texture *texture = NULL;
        Texture *specTexture = NULL;
        Shader *shader;

        void listenInputs();
        void bindTexture();
        void setStaticShaderUniforms();
};

#endif