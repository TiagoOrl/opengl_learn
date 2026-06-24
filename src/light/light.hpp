#ifndef H_CLASS_LIGHT
#define H_CLASS_LIGHT

#include "../transform/transform.hpp"
#include "../shader/shader.hpp"
#include "../vao/vao.hpp"
#include "../vbo/vbo.hpp"
#include "../camera/camera.hpp"
#include <format>


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
        inline Light(GLFWwindow *window, Camera *camera, Shader *srcShader, Shader* dstShader, int index,  float x, float y, float z);
        inline Light(GLFWwindow *window, Camera *camera, Shader *srcShader, Shader* dstShader, int index, const glm::vec3 &coord);
        inline void setVerticesData(float vertices[], GLuint arraySize, int drawType);
        inline void setProperties(properties prop);
        inline void listenInputs();
        inline void draw();
        inline glm::vec3 getPosition() const;
        properties prop;
    private:
        int pos;
        VAO *vao = NULL;
        VBO *vbo = NULL;
        Camera *camera = NULL;
        Shader *srcShader = NULL;
        Shader *dstShader = NULL;
        GLFWwindow *window = NULL;
};


inline glm::vec3 Light::getPosition() const { return transform->position;}

inline Light::Light(GLFWwindow *window, Camera *camera, Shader *srcShader, Shader* dstShader, int index, float x, float y, float z) 
    : camera(camera), srcShader(srcShader), dstShader(dstShader), window(window), pos(index) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
    transform = new Transform(x, y, z);
}


inline Light::Light(GLFWwindow *window, Camera *camera, Shader *srcShader, Shader* dstShader, int index, const glm::vec3 &coord) 
    : camera(camera), srcShader(srcShader), dstShader(dstShader), window(window), pos(index) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
    transform = new Transform(coord.x, coord.y, coord.z);
}


inline void Light::setProperties(properties prop) {
    this->prop = prop;
}


inline void Light::listenInputs() {
    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) 
        transform->addX();

    else if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) 
        transform->decX();

    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) 
        transform->addZ();

    else if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS) 
        transform->decZ();

    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        transform->decY();

    else if(glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        transform->addY();
}


inline void Light::setVerticesData(float vertices[], GLuint arraySize, int drawType) {
    vao = new VAO(vbo, vertices, arraySize, drawType);

    vao->setVertexAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao->setVertexAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), 3);
    vao->setVertexAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), 6);
}


inline void Light::draw() {
    dstShader->use();
    dstShader->setVec3(std::format("lights[{}].position", pos), &transform->position[0]);
    dstShader->setVec3(std::format("lights[{}].diffuse", pos),  &prop.diffuse[0]); 
    dstShader->setVec3(std::format("lights[{}].specular", pos), &prop.specular[0]); 

    dstShader->setFloat(std::format("lights[{}].constant", pos), prop.constant);
    dstShader->setFloat(std::format("lights[{}].linear", pos), prop.linear);
    dstShader->setFloat(std::format("lights[{}].quadratic", pos), prop.quadratic);


    srcShader->use();
    srcShader->setVec3("diffuse", &glm::vec3(1.0f)[0]);

    listenInputs();

    srcShader->setProjection(camera->projection, std::string("projection"));
    srcShader->setView(camera->view, std::string("view"));
    srcShader->setModel(transform->model, std::string("model"));



    vao->bind();
}

#endif