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


void Shader::use() {
    glUseProgram(ID);
}

void Shader::updateColorUniform(const char * name, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    int vertexColorLocation = glGetUniformLocation(ID, name);
    glUniform4f(vertexColorLocation, r, g, b, a);
}   


void Shader::wipe() {
    glDeleteProgram(ID);
}


void Shader::setTransform(const glm::mat4 trans, const std::string &name) {
    GLuint transLoc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
}


void Shader::set3DProjection(
    const glm::mat4 &model, 
    const glm::mat4 &view, 
    const glm::mat4 &projection,
    const std::string &modelName,
    const std::string &viewName,
    const std::string &projectionName
) const {
    setMat4Pointer(modelName, model);
    setMat4(viewName, view);
    setMat4(projectionName, projection);
}


void Shader::setMat4Pointer(const std::string &name, const glm::mat4 &mat) const 
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}


void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}


void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}


void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}


void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 