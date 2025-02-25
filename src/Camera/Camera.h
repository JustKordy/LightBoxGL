#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

 
class Camera
{
public: 

    Camera();
    ~Camera();

    void HandleInput(GLFWwindow *window);
    void HandleLook(double xposIn, double yposIn, bool mouseClicked);
    void HandleZoom(double yoffset);

    void Update();

    glm::mat4& GetProjection(){
        return this->m_Projection;
    }

    glm::mat4& GetView(){
        return this->m_View;
    }

    float& GetFov(){
        return this->m_Fov;
    }

    glm::vec3& GetPosition() {
        return this->m_CameraPos;
    }

private:
    glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 m_Projection;
    glm::mat4 m_View;

    bool m_FirstMouse = true;
    float m_CameraSpeed = 0.5f;
    float m_Yaw = -90.0f; 
    float m_Pitch = 0.0f;

    float m_LastX = 800.0f / 2.0;
    float m_LastY = 600.0 / 2.0;
    float m_Fov = 45.0f;
};