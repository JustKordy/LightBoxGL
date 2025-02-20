
#include "Shader.h"
#include "../Logger/Logger.h"
#include <fstream>


Shader::Shader(const char *vertexPath, const char *fragmentPath){
    std::string vertexSource;
    std::string fragmentSource;

    ASSERT(vertexPath, "the path param is nullptr");

    std::string line;

    std::ifstream f(vertexPath);
    ASSERT(f, "Vertex shader path is wrong");
    if(f.is_open())
    { 
        Logger::Log("opened file1");
        while(std::getline(f, line))
        {
            vertexSource += line + " \n";
        }
        f.close();
    }
    
    line = "";
    std::ifstream f2(fragmentPath);
    ASSERT(f2, "fragment shader path is wrong");
    if(f2.is_open())
    { 
        Logger::Log("opened file2");
        while(std::getline(f2, line))
        {
            fragmentSource += line + " \n";
        }
        f2.close();
    }

    const char* vertSource = vertexSource.c_str();
    const char* fragSource = fragmentSource.c_str();
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Link shaders
    m_Id = glCreateProgram();
    glAttachShader(m_Id, fragmentShader);
    glAttachShader(m_Id, vertexShader);
    glLinkProgram(m_Id);
    // Check for linking errors
    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
}

void Shader::use(){
    glUseProgram(m_Id);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value); 
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat4)
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec3)
{
    glUniform3fv(glGetUniformLocation(m_Id, name.c_str()), 1, &vec3[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(m_Id, name.c_str()), x, y, z); 
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_Id, name.c_str()), x, y, z, w); 
}
void Shader::setVec4(const std::string &name, const glm::vec4& vec4)
{
    glUniform4fv(glGetUniformLocation(m_Id, name.c_str()), 1, &vec4[0]);
}

