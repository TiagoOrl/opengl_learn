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
#include "src/Position.hpp"

#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float texVisibility = 0.2f;
Position position(0.2f, 0.2f);


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


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    
    float triangle1[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right 
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top   
    }; 

    float triangle2[] = {
        0.20f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f, // left  
        0.90f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, // right 
        0.48f,  0.98f, 0.0f, 1.0f, 0.0f, 0.0f // top     
    }; 

    float texScale = 2.0f;

    float square[] = {
        // positions          // colors           // texture coords (note that we changed them to 2.0f!)
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   texScale, texScale, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   texScale, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f,     0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,     texScale  // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shader1("shaders/default.vert", "shaders/default.frag");
    VAO vao1(square, sizeof(square), 3, GL_STATIC_DRAW, 8 * sizeof(float), 3, 6);
    EBO ebo1(indices, sizeof(indices));
    

    Texture texture1(std::string("./images/container.jpg"), GL_RGB, GL_TEXTURE0);
    Texture texture2(std::string("./images/awesomeface.png"), GL_RGBA, GL_TEXTURE1);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader1.activate();
    shader1.setInt("texture2", 1);

    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float val1 = sin(timeValue * 2) / 1.0f + 0.5f;
        float val2 = cos(timeValue * 2) / 1.0f + 0.5f;

        shader1.activate();
        shader1.setFloat(std::string("shValue"), val1);
        shader1.setFloat(std::string("texVisibility"), texVisibility);

        
        shader1.setTransform(position.trans, std::string("transform"));
        position.rotate3d();
        shader1.setProjection(
            position.model, 
            position.view, 
            position.projection,
            std::string("model"), 
            std::string("view")
        );

        vao1.bind();

        texture1.activate();
        texture1.bind();

        texture2.activate();
        texture2.bind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao1.unbind();
    ebo1.unbind();
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
        position.rotate(0.003f);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        position.rotate(-0.003f);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position.moveVertical(0.002f);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position.moveVertical(-0.002f);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position.moveHorizontal(0.002f);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position.moveHorizontal(-0.002f);
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

