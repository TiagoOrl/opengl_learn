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

    auto cube = new Object(window, 1.0f, 3.55f, 1.2f);
    auto lightsource = new Light(window, -0.5f, 1.8f, -2.0f);
    

    cube->setShaders("./shaders/cube.vert", "./shaders/cube.frag");
    cube->setTexture("./images/container2.png", "./images/container2_specular.png", GL_TEXTURE0);
    cube->setVerticesData(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);
    
    cube->transform->changeScale(2.8f);

    lightsource->setShaders("shaders/light_source.vert", "shaders/light_source.frag");
    lightsource->setVerticesData(vbo, cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);


    cube->setLight({
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });
    


    Camera camera(glm::vec3(0.0f, 5.24f, -7.0f));
    camera.rotate(0.0f, -17.0f);


    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    camera.createProjection();
    cube->setShaderUniforms();

    
    while (!glfwWindowShouldClose(window))
    {
        time_utils::calcDeltaTime();
        
        controller.listenInputs(window, texVisibility);
        camera.listenInputs(window);

        glClearColor(0.03f, 0.08f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.lookAt();

        //draw box cube
        cube->draw(camera, lightsource);

        //draw lamp object
        lightsource->draw(camera);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo->unbind();
    cube->unbind();
    lightsource->unbind();


    delete vbo;


    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

