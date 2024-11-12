#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/gtc/type_ptr.hpp>


std::string getFileContents(const char* filename);

class Shader {
    public:
        GLuint ID;
        Shader(const char* vertexFile, const char* fragmentFile);

        void use();
        void updateColorUniform(const char * name, GLfloat r, GLfloat g, GLfloat b, GLfloat a);

        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void setMat4Pointer(const std::string &name, const glm::mat4 &mat) const;

        void setTransform(const glm::mat4 trans, const std::string &name);
        void set3DProjection(
            const glm::mat4 &model, 
            const glm::mat4 &view,
            const glm::mat4 &projection,
            const std::string &modelName,
            const std::string &viewName,
            const std::string &projectionName
        ) const;

        void wipe();


};





#endif