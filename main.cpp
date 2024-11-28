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
Transform cubeTransform(0.0f, 0.0f, -1.0f);
Transform lightsourceTransform(1.2f, 1.0f, 2.0f);


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


    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    Controller controller;
    // Shader shader1("shaders/default3d.vert", "shaders/default.frag");
    Shader lightingShader("shaders/cube.vert", "shaders/cube.frag");
    Shader lightCubeShader("shaders/light_source.vert", "shaders/light_source.frag");

    VBO vbo(GL_ARRAY_BUFFER);
    VAO cubeVAO(vbo, cube, sizeof(cube), GL_STATIC_DRAW, 5 * sizeof(float), 3);
    VAO lightVAO(vbo, cube, sizeof(cube), GL_STATIC_DRAW, 5 * sizeof(float), 3);
    Camera camera;
    
    // EBO ebo1(indices, sizeof(indices));
    

    Texture texture1(std::string("./images/container.jpg"), GL_RGB, GL_TEXTURE0);
    Texture texture2(std::string("./images/awesomeface.png"), GL_RGBA, GL_TEXTURE1);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    
    // shader1.setInt("texture1", 0);
    // shader1.setInt("texture2", 1);


    camera.createProjection();


    
    while (!glfwWindowShouldClose(window))
    {
        time_utils::calcDeltaTime();
        
        controller.listenInputs(window, texVisibility);
        camera.listenInputs(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.bind();
        texture2.bind();

        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);

        camera.createView();
        lightingShader.setProjection(camera.projection, std::string("projection"));
        lightingShader.setView(camera.view, std::string("view"));

        cubeTransform.applyTransform(glm::vec3(1.0f), 0);
        cubeTransform.scale(glm::vec3(1.22f));

        lightingShader.setModel(cubeTransform.model, std::string("model"));

        cubeVAO.bind();


        //draw lamp object
        lightCubeShader.use();

        lightCubeShader.setProjection(camera.projection, std::string("projection"));
        lightCubeShader.setView(camera.view, std::string("view"));

        lightsourceTransform.applyTransform(glm::vec3(1.2f, 1.0f, 2.0f), 0);
        lightsourceTransform.scale(glm::vec3(0.33f));

        lightCubeShader.setModel(lightsourceTransform.model, std::string("model"));


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

