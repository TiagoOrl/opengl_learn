#include "Object.hpp"



Object::Object(GLFWwindow *window, float x, float y, float z) {
    this->window = window;
    transform = new Transform(x, y, z);
}


void Object::setVerticesData(VBO *vbo, float vertices[], GLuint arraySize, int drawType) {
    vao = new VAO(vbo, vertices, arraySize, drawType);

    vao->setVertexAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao->setVertexAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), 3);
    vao->setVertexAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), 6);
}


void Object::setTexture(const std::string &imgPath, const std::string &specularPath, GLint position) {
    texture = new Texture(imgPath, position);
    specTexture = new Texture(specularPath, position + 1);
}


void Object::setShaders(const char* vertexFile, const char* fragmentFile) {
    shader = new Shader(vertexFile, fragmentFile);
}

void Object::bindTexture() {
    texture->activate();
    texture->bind();
    specTexture->activate();
    specTexture->bind();
}


void Object::setShaderUniforms() {
    shader->use();
    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
}


void Object::setLight(LightMaterial light) {
    this->light = light;
}


void Object::draw(Camera camera, Object *lightsource) {
    shader->use();
    
    shader->setVec3("light.ambient",  light.ambient);
    shader->setVec3("light.diffuse",  light.diffuse); 
    shader->setVec3("light.specular", light.specular); 
    
    shader->setFloat("material.shininess", 64.0f);

    shader->setVec3("lightPos", lightsource->transform->position);
    shader->setVec3("viewPos", camera.position);


    shader->setProjection(camera.projection, std::string("projection"));
    shader->setView(camera.view, std::string("view"));

    transform->incrementAngle(6.0f);
    transform->update();
    transform->listenInputs(window);

    shader->setModel(transform->model, std::string("model"));

    bindTexture();

    vao->bind();
}


void Object::unbind() {
    vao->unbind();
    shader->wipe();

    delete vao;
    delete shader;
    delete texture;
    delete specTexture;
    delete transform;
}