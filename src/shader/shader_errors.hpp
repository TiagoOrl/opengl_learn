#ifndef SHADER_ERRORS_H
#define SHADER_ERRORS_H


#include <glad/glad.h>
#include <iostream>


int shaderCheck(unsigned int shader) {
    int success;
    char infoLog[512];


    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return success;
}


#endif