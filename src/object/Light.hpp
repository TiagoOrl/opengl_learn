#ifndef H_CLASS_LIGHT
#define H_CLASS_LIGHT

#include "./transform/Transform.hpp"
#include "./texture/Texture.hpp"
#include "./shader/Shader.hpp"
#include "./vao/VAO.hpp"
#include "./vbo/VBO.hpp"
#include "../camera/Camera.hpp"


struct _properties {
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

typedef struct _properties properties;

class Light {
    public:
        Transform *transform = NULL;
        inline Light(GLFWwindow *window, Camera *camera, Shader *shader, float x, float y, float z);
        inline Light(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &pos);
        inline void setVerticesData(float vertices[], GLuint arraySize, int drawType);
        inline void setProperties(properties prop);
        inline void draw();
        inline glm::vec3 getPosition() const;
        properties prop;
    private:
        VAO *vao = NULL;
        VBO *vbo = NULL;
        Camera *camera = NULL;
        Texture *texture = NULL;
        Shader *shader = NULL;
        GLFWwindow *window = NULL;
};


inline glm::vec3 Light::getPosition() const { return transform->position;}

inline Light::Light(GLFWwindow *window, Camera *camera, Shader *shader, float x, float y, float z) 
    : camera(camera), shader(shader), window(window) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
    transform = new Transform(x, y, z);
}


inline Light::Light(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &coord) 
    : camera(camera), shader(shader), window(window) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
    transform = new Transform(coord.x, coord.y, coord.z);
}

inline void Light::setProperties(properties prop) {
    this->prop = prop;
}


inline void Light::setVerticesData(float vertices[], GLuint arraySize, int drawType) {
    vao = new VAO(vbo, vertices, arraySize, drawType);

    vao->setVertexAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao->setVertexAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), 3);
    vao->setVertexAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), 6);
}


inline void Light::draw() {
    shader->use();
    
    shader->setVec3("diffuse", &glm::vec3(1.0f)[0]);

    shader->setProjection(camera->projection, std::string("projection"));
    shader->setView(camera->view, std::string("view"));


    shader->setModel(transform->model, std::string("model"));


    vao->bind();
}

#endif