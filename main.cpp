#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "src/object/Object.hpp"
#include "src/object/Light.hpp"
#include "src/camera/Camera.hpp"

#include "src/time/Time.hpp"

#include "src/controller/Controller.hpp"

#include "src/_vertices.hpp"
#include "src/config.hpp"

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

    std::vector<Object *> objects{};

    auto lightsource = new Light(window, -0.5f, 1.8f, -2.0f);
    lightsource->setDirection(glm::vec3(-0.2f, -1.0f, -0.3f));

    for (int i = 0;i < 7; i++) {
        auto cube = new Object(window, coords[i]);

        cube->setShaders("./shaders/cube.vert", "./shaders/cube.frag");
        cube->setTexture("./images/container2.png", "./images/container2_specular.png", GL_TEXTURE0);
        cube->setVerticesData(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);
        
        cube->transform->changeScale(1.8f);

        cube->setLight({
            lightsource->getPosition(),
            lightsource->getDirection(),
            glm::vec3(0.2f, 0.2f, 0.2f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        });

        cube->setShaderUniforms();

        objects.push_back(cube);
    }

    
    
    lightsource->setShaders("shaders/light_source.vert", "shaders/light_source.frag");
    lightsource->setVerticesData(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);


    Camera camera(glm::vec3(0.0f, 5.24f, -7.0f));
    camera.rotate(0.0f, -17.0f);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    camera.createProjection();
    

    
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
        

        //draw lamp object
        lightsource->draw(camera);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo->unbind();


    delete vbo;
    for (auto i : objects) 
        delete i;

    delete lightsource;

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

