#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "src/Shader.hpp"
#include "src/VAO.hpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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

    // glfw window creation
    // --------------------
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


    
    Shader shader1("shaders/default.vert", "shaders/default.frag");
    Shader shader2("shaders/default.vert", "shaders/default2.frag");
    
    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
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

    VAO vao1(triangle1, sizeof(triangle1), 3, GL_STATIC_DRAW, 0, 3, GL_FLOAT, 6, 1, 3);
    VAO vao2(triangle2, sizeof(triangle2), 3, GL_STATIC_DRAW, 0, 3, GL_FLOAT, 6, 1, 3);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // float timeValue = glfwGetTime();
        // float val1 = sin(timeValue) / 1.0f + 0.5f;
        // float val2 = cos(timeValue) / 1.0f + 0.5f;

        shader1.activate();
        // shader1.updateColorUniform("sharedColor", val1, val2, 1.0f, 1.0f);
        vao1.bind();

        

        shader2.activate();
        vao2.bind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    vao1.unbind();
    vao2.unbind();
    shader1.wipe();
    shader2.wipe();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

