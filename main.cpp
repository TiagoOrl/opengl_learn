#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "src/shader/Shader.hpp"
#include "src/vao/VAO.hpp"
#include "src/vbo/VBO.hpp"
#include "src/ebo/EBO.hpp"
#include "src/texture/Texture.hpp"
#include "src/transform/Transform.hpp"
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


    GLFWwindow* window = glfwCreateWindow(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "Black 2", NULL, NULL);
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

    Shader lightingShader("shaders/cube.vert", "shaders/cube.frag");
    Shader lightCubeShader("shaders/light_source.vert", "shaders/light_source.frag");

    Transform cube(-0.3f, 1.0f, -1.0f);
    Transform lightsource(0.2f, 0.73f, 1.0f);

    VBO vbo(GL_ARRAY_BUFFER);
    VAO cubeVAO(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);
    cubeVAO.setVertexAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), 0);
    cubeVAO.setVertexAttribute(1, 3, GL_FLOAT, 6 * sizeof(float), 3);

    VAO lightVAO(vbo, GL_STATIC_DRAW);
    lightVAO.setVertexAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), 0);

    Camera camera(glm::vec3(0.0f, 1.24f, -5.0f));
    auto lightPos = glm::vec3(-0.5f, 1.8f, -2.0f);

    

    Texture texture1(std::string("./images/container.jpg"), GL_RGB, GL_TEXTURE0);
    Texture texture2(std::string("./images/awesomeface.png"), GL_RGBA, GL_TEXTURE1);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    camera.createProjection();


    
    while (!glfwWindowShouldClose(window))
    {
        time_utils::calcDeltaTime();
        
        controller.listenInputs(window, texVisibility);
        camera.listenInputs(window);

        glClearColor(0.01f, 0.08f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.bind();
        texture2.bind();

        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        camera.createView();
        lightingShader.setProjection(camera.projection, std::string("projection"));
        lightingShader.setView(camera.view, std::string("view"));

        cube.applyTransform(glm::vec3(1.0f, 0.55f, 2.0f));

        lightingShader.setModel(cube.model, std::string("model"));

        cubeVAO.bind();


        //draw lamp object
        lightCubeShader.use();

        lightCubeShader.setProjection(camera.projection, std::string("projection"));
        lightCubeShader.setView(camera.view, std::string("view"));

        lightsource.applyTransform(lightPos);
        lightsource.scale(glm::vec3(0.33f));

        lightCubeShader.setModel(lightsource.model, std::string("model"));


        lightVAO.bind();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo.unbind();
    cubeVAO.unbind();
    lightVAO.unbind();
    // ebo1.unbind();
    lightingShader.wipe();
    lightCubeShader.wipe();


    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

