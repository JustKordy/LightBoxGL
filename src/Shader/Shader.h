#pragma once
#include <GL/glew.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader
{
public:
    // the program ID
    unsigned int m_Id;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string& name, const glm::mat4 &mat4);
    void setVec3(const std::string& name, const glm::vec3 &vec3);
    void setVec3(const std::string &name, float x, float y, float z);
};