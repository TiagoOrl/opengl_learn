#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>


std::string getFileContents(const char* filename);

class Shader {
    public:
        GLuint ID;
        Shader(const char* vertexFile, const char* fragmentFile);

        void activate();
        void updateColorUniform(const char * name, GLfloat r, GLfloat g, GLfloat b, GLfloat a);

        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;

        void wipe();


};





#endif