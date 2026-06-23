#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./object/light/light.hpp"
#include "./object/object.hpp"
#include "./object/light/spotlight.hpp"
#include "./object/light/directlight.hpp"
#include "./camera/camera.hpp"

#include "./time/time.hpp"

#include "./controller/controller.hpp"

#include "./_vertices.hpp"
#include "./config.hpp"

#include <iostream>
#include <string>
#include <vector>

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


    GLFWwindow* window = glfwCreateWindow(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "Guava Engine dev", NULL, NULL);
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


    std::vector<glm::vec3> lightPositions = {
        glm::vec3( 0.7f,  7.2f,  2.0f),
        glm::vec3( 2.3f, 5.3f, -4.0f),
        glm::vec3(-4.0f,  -8.0f, -12.0f),
        glm::vec3( 5.0f,  0.0f, 0.0f)
    };

    std::vector<Light *> pointLights{};


    auto camera =  new Camera(glm::vec3(0.0f, 5.24f, -7.0f));
    camera->rotate(0.0f, -17.0f);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    camera->createProjection();

    auto objShader = new Shader("./shaders/cube.vert", "./shaders/cube.frag");
    auto lightSrcShader = new Shader("shaders/light_source.vert", "shaders/light_source.frag");

    auto directLight = new DirectLight(
        lightSrcShader,
        glm::vec3(-0.2f, -1.0f, -0.3f), 
        glm::vec3(0.05f, 0.05f, 0.05f), 
        glm::vec3(0.4f, 0.4f, 0.4f),
        glm::vec3(1.5f, 1.5f, 1.5f)
    );

    

    Spotlight * spotlight = new Spotlight(
        objShader, 
        camera, 
        .5f, 17.5f, 
        glm::vec3(2.5f, 2.5f, 2.5f), 
        glm::vec3(1.0f, 4.3f, 1.55f),
        1.0f, 0.09f, 0.032f
    );


    for (int i = 0; i < lightPositions.size(); i++)
    {
        auto light = new Light(window, camera, lightSrcShader, objShader, i, lightPositions[i]);
        light->setVerticesData(cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);
        light->setProperties({
            glm::vec3(1.5f, 1.5f, 1.5f),
            glm::vec3(5.0f, 5.0f, 5.0f),
            1.0f,
            0.09f,
            0.032f
        });

        pointLights.push_back(light);
    }

    while (!glfwWindowShouldClose(window))
    {
        time_utils::calcDeltaTime();
        
        controller.listenInputs(window, texVisibility);
        camera->listenInputs(window);

        glClearColor(0.03f, 0.08f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->lookAt();

        for (auto light: pointLights) {
            light->draw();
        }
        
        spotlight->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    objShader->wipe();
    lightSrcShader->wipe();
    
    for (auto i : pointLights)
        delete i;

    delete objShader;
    delete lightSrcShader;

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

