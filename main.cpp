#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "src/object/shader/Shader.hpp"
#include "src/object/vao/VAO.hpp"
#include "src/object/vbo/VBO.hpp"
#include "src/object/ebo/EBO.hpp"
#include "src/object/texture/Texture.hpp"
#include "src/object/transform/Transform.hpp"
#include "src/camera/Camera.hpp"

#include "src/time/Time.hpp"

#include "src/controller/Controller.hpp"

#include "src/_vertices.hpp"
#include "src/config.hpp"

#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings

float texVisibility = 0.2f;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "GameEngine XL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Controller controller;

    Shader cubeShader("shaders/cube.vert", "shaders/cube.frag");
    Shader lightSourceShader("shaders/light_source.vert", "shaders/light_source.frag");

    Transform cube(1.0f, 3.55f, 1.2f);
    Transform lightsource(-0.5f, 1.8f, -2.0f);

    cube.changeScale(2.8f);

    VBO vbo(GL_ARRAY_BUFFER);
    VAO cubeVAO(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);
    cubeVAO.setVertexAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    cubeVAO.setVertexAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), 3);
    cubeVAO.setVertexAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), 6);

    VAO lightVAO(vbo, GL_STATIC_DRAW);
    lightVAO.setVertexAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    lightVAO.setVertexAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), 3);
    lightVAO.setVertexAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), 6);

    Camera camera(glm::vec3(0.0f, 5.24f, -7.0f));
    camera.rotate(0.0f, -17.0f);

    Texture texture1(std::string("./images/container2.png"), GL_TEXTURE0);
    Texture texture1SpecularMap(std::string("./images/container2_specular.png"), GL_TEXTURE1);


    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    camera.createProjection();

    cubeShader.use();
    cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);

    
    while (!glfwWindowShouldClose(window))
    {
        time_utils::calcDeltaTime();
        
        controller.listenInputs(window, texVisibility);
        camera.listenInputs(window);

        glClearColor(0.03f, 0.08f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        cubeShader.use();

    
        cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);

        
        cubeShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
        cubeShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); 
        cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f); 
        
        cubeShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        cubeShader.setFloat("material.shininess", 32.0f);

        cubeShader.setVec3("lightPos", lightsource.position);
        cubeShader.setVec3("viewPos", camera.position);

        camera.createView();
        cubeShader.setProjection(camera.projection, std::string("projection"));
        cubeShader.setView(camera.view, std::string("view"));

        cube.incrementAngle(4.0f);
        cube.update();
        cube.listenInputs(window);

        cubeShader.setModel(cube.model, std::string("model"));

        texture1.activate();
        texture1.bind();
        texture1SpecularMap.activate();
        texture1SpecularMap.bind();

        cubeVAO.bind();


        //draw lamp object
        lightSourceShader.use();

        lightSourceShader.setProjection(camera.projection, std::string("projection"));
        lightSourceShader.setView(camera.view, std::string("view"));

        lightsource.update();


        lightSourceShader.setModel(lightsource.model, std::string("model"));
        lightSourceShader.setVec3("diffuse", glm::vec3(1.0f));

    

        lightVAO.bind();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo.unbind();
    cubeVAO.unbind();
    lightVAO.unbind();
    // ebo1.unbind();
    cubeShader.wipe();
    lightSourceShader.wipe();


    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

