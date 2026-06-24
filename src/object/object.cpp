#include "./object.hpp"
#include <stdexcept>
#include <string>


Object::Object(GLFWwindow *window, Camera *camera, Shader *shader, const glm::vec3 &coord)
    : shader(shader), camera(camera), window(window) {
    this->vbo = new VBO(GL_ARRAY_BUFFER);
    transform = new Transform(coord.x, coord.y, coord.z);
    setStaticShaderUniforms();
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


void Object::setStaticShaderUniforms() {
    shader->use();
    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
    shader->setFloat("material.shininess", 64.0f);
}


glm::vec3 Object::getPosition() const {
    return transform->position;
}


void Object::listenInputs() {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        transform->addX();

    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        transform->decX();

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
        transform->addZ();

    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
        transform->decZ();

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        transform->decY();

    else if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        transform->addY();

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        transform->incrementScale(0.4f);

    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        transform->incrementScale(-0.4f);
}


void Object::scale(GLfloat scale) {
    transform->changeScale(scale);
}


void Object::draw() {
    shader->use();
    shader->setVec3("viewPos", &camera->position[0]);


    shader->setProjection(camera->projection, std::string("projection"));
    shader->setView(camera->view, std::string("view"));
    shader->setModel(transform->model, std::string("model"));
    transform->incrementAngle(0.44f);
    listenInputs();

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