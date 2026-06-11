#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "./object/Object.hpp"
#include "./object/Light.hpp"
#include "./object/Spotlight.hpp"
#include "./object/DirectLight.hpp"
#include "./camera/Camera.hpp"

#include "./time/Time.hpp"

#include "./controller/Controller.hpp"

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

    VBO *vbo = new VBO(GL_ARRAY_BUFFER);

    glm::vec3 coords[] = {
        glm::vec3(1.0f, 3.55f, 1.2f),
        glm::vec3(2.0f, 0.0f, 3.2f),
        glm::vec3(4.0f, 3.55f, -1.2f),
        glm::vec3(-1.0f, 2.0f, -4.2f),
        glm::vec3(-6.0f, -1.55f, 1.2f),
        glm::vec3(12.4f, -7.55f, -7.2f),
        glm::vec3(-1.0f, 0.55f, 0.2f)
    };

    glm::vec3 lightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    std::vector<Object *> objects{};
    std::vector<Light *> pointLights{};


    Camera camera(glm::vec3(0.0f, 5.24f, -7.0f));
    camera.rotate(0.0f, -17.0f);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    camera.createProjection();

    auto boxShader = new Shader("./shaders/cube.vert", "./shaders/cube.frag");
    auto lightShader = new Shader("shaders/light_source.vert", "shaders/light_source.frag");

    auto lightsource = new Light(window, lightShader, -0.5f, 1.8f, -2.0f);
    auto directLight = new DirectLight(
        lightShader,
        glm::vec3(-0.2f, -1.0f, -0.3f), 
        glm::vec3(0.05f, 0.05f, 0.05f), 
        glm::vec3(0.4f, 0.4f, 0.4f),
        glm::vec3(1.5f, 1.5f, 1.5f)
    );

    

    Spotlight * spotlight = new Spotlight(boxShader, .5f, 17.5f, glm::vec3(2.5f, 2.5f, 2.5f), glm::vec3(1.0f, 4.3f, 1.55f));


    for (int i = 0; i < sizeof(lightPositions) / sizeof(glm::vec3); i++)
    {
        auto light = new Light(window, lightShader, lightPositions[i]);
        light->setVerticesData(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);

        pointLights.push_back(light);
    }

    for (int i = 0;i < sizeof(coords) / sizeof(glm::vec3); i++) {
        auto cube = new Object(window, boxShader, coords[i]);

        cube->setTexture("./images/container2.png", "./images/container2_specular.png", GL_TEXTURE0);
        cube->setVerticesData(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);
        
        cube->transform->changeScale(1.8f);

        cube->setLight({
            lightsource->getPosition(),
            glm::vec3(1.5f, 1.5f, 1.5f),
            glm::vec3(5.0f, 5.0f, 5.0f),
            1.0f,
            0.09f,
            0.032f
        });

        cube->setShaderUniforms();

        objects.push_back(cube);
    }

    
    lightsource->setVerticesData(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);
    

    
    while (!glfwWindowShouldClose(window))
    {
        time_utils::calcDeltaTime();
        
        controller.listenInputs(window, texVisibility);
        camera.listenInputs(window);

        glClearColor(0.03f, 0.08f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.lookAt();

        //draw box cube
        for (auto cube : objects) {
            cube->draw(camera, lightsource);
        }

        for (auto light: pointLights) {
            light->draw(camera);
        }
        
        lightsource->draw(camera);
        spotlight->draw(camera);
        directLight->draw();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo->unbind();
    boxShader->wipe();
    lightShader->wipe();


    delete vbo;
    for (auto i : objects) 
        delete i;

    delete lightsource;
    delete boxShader;
    delete lightShader;

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

