#include "Object.hpp"


Object::Object(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &coord)
    : shader(shader), camera(camera), window(window) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
    transform = new Transform(coord.x, coord.y, coord.z);
}


Object::Object(GLFWwindow *window, Camera *camera, Shader *shader, float x, float y, float z)
    : shader(shader), camera(camera), window(window) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
    transform = new Transform(x, y, z);
}


void Object::setVerticesData(float vertices[], GLuint arraySize, int drawType) {
    vao = new VAO(vbo, vertices, arraySize, drawType);

    vao->setVertexAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao->setVertexAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), 3);
    vao->setVertexAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), 6);
}


void Object::setTexture(const std::string imgPath, const std::string &specularPath, GLint position) {
    texture = new Texture(imgPath, position);
    specTexture = new Texture(specularPath, position + 1);
}


void Object::bindTexture() {
    if (texture == NULL || specTexture == NULL)
        throw std::runtime_error("texture error(32): texture is not created = NULL");

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


void Object::setMaterial(Material light) {
    this->material = light;
}


glm::vec3 Object::getPosition() const {
    return transform->position;
}


void Object::draw(Object *lightsource) {
    shader->use();

    if (!material.has_value()) 
        throw std::runtime_error("object error(60): material undefined");
    
    
    shader->setVec3("light.position", &lightsource->transform->position[0]);
    shader->setVec3("light.diffuse",  &material->diffuse[0]); 
    shader->setVec3("light.specular", &material->specular[0]); 

    shader->setFloat("light.constant", material->constant);
    shader->setFloat("light.linear", material->linear);
    shader->setFloat("light.quadratic",material->quadratic);
    
    shader->setFloat("material.shininess", 64.0f);

    shader->setVec3("viewPos", &camera->position[0]);


    shader->setProjection(camera->projection, std::string("projection"));
    shader->setView(camera->view, std::string("view"));

    // transform->incrementAngle(6.0f);
    transform->update();
    transform->listenInputs(window);

    shader->setModel(transform->model, std::string("model"));

    bindTexture();

    vao->bind();
}


Object::~Object() {

    std::cout << "Object destroyed... \n";
    
    vao->unbind();
    vbo->unbind();

    delete vao;
    delete vbo;
    delete texture;
    delete specTexture;
    delete transform;
}