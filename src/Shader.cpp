#include "Shader.hpp"
#include "shader_errors.hpp"



std::string getFileContents(const char* filename) {
    std::ifstream in(filename, std::ios::binary);

    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }

    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) { 
    std::string vertexCode = getFileContents(vertexFile);
    std::string fragmentCode = getFileContents(fragmentFile);

    const char * vertexShaderSrc = vertexCode.c_str();
    const char * fragmentShaderSrc = fragmentCode.c_str();


    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);
    shaderCheck(vertexShader);


    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);
    shaderCheck(fragmentShader);


    // shader program init...
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    shaderCheck(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::activate() {
    glUseProgram(ID);
}


void Shader::wipe() {
    glDeleteProgram(ID);
}