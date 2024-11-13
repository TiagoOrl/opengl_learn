#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "src/Shader.hpp"
#include "src/VAO.hpp"
#include "src/EBO.hpp"
#include "src/Texture.hpp"
#include "src/Transform.hpp"

#include "src/_vertices.hpp"

#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float texVisibility = 0.2f;
Transform transform(0.2f, 0.2f);


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


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Black 2", NULL, NULL);
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

    Shader shader1("shaders/default3d.vert", "shaders/default.frag");

    VAO cubeVAO(cube, sizeof(cube), GL_STATIC_DRAW, 5 * sizeof(float), 3);
    
    // EBO ebo1(indices, sizeof(indices));
    

    Texture texture1(std::string("./images/container.jpg"), GL_RGB, GL_TEXTURE0);
    Texture texture2(std::string("./images/awesomeface.png"), GL_RGBA, GL_TEXTURE1);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader1.use();
    shader1.setInt("texture1", 0);
    shader1.setInt("texture2", 1);

    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.bind();
        texture2.bind();

        shader1.use();
        
        transform.apply();

        shader1.set3DProjection(
            transform.model, 
            transform.view, 
            transform.projection,
            std::string("model"), 
            std::string("view"),
            std::string("projection")
        );

        shader1.setFloat(std::string("texVisibility"), texVisibility);

        cubeVAO.bind();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cubeVAO.unbind();
    // ebo1.unbind();
    shader1.wipe();


    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (texVisibility < 1.0f) 
            texVisibility += 0.001f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (texVisibility > 0.0f) 
            texVisibility -= 0.001f;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        transform.rotate(0.003f);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        transform.rotate(-0.003f);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        transform.moveVertical(0.002f);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        transform.moveVertical(-0.002f);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        transform.moveHorizontal(0.002f);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        transform.moveHorizontal(-0.002f);
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

