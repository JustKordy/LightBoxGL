#include "Camera.h"
#include "../Utils/Utils.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}


void Camera::HandleInput(GLFWwindow *window)
{
    


    const float cameraSpeed = 5.0f; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_CameraPos += cameraSpeed * m_CameraFront * Utils::GetDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_CameraPos -= cameraSpeed * m_CameraFront * Utils::GetDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_CameraPos += cameraSpeed * m_CameraUp * Utils::GetDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_CameraPos -= cameraSpeed * m_CameraUp * Utils::GetDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed * Utils::GetDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed * Utils::GetDeltaTime();


}

void Camera::HandleLook(double xposIn, double yposIn, bool mouseClicked)
{
    if (mouseClicked)
    {
        // Convert screen coordinates to relative movement
        float inPosX = xposIn - SCREEN_WIDTH_HALF;
        float inPosY = yposIn - SCREEN_HEIGHT_HALF;

        if (m_FirstMouse)
        {
            m_LastX = inPosX;
            m_LastY = inPosY;
            m_FirstMouse = false;
        }

        float xoffset = inPosX - m_LastX;
        float yoffset = m_LastY - inPosY; // Inverted Y-axis

        m_LastX = inPosX;
        m_LastY = inPosY;

        float sensitivity = 0.2f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        // Clamp the pitch to avoid screen flip
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        // Update the camera front vector based on yaw and pitch
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_CameraFront = glm::normalize(front);
    }
    else
    {
        m_FirstMouse = true;
    }
}

void Camera::HandleZoom(double yoffset)
{
    m_Fov -= (float)yoffset;
    if (m_Fov < 1.0f)
        m_Fov = 1.0f;
    if (m_Fov > 45.0f)
        m_Fov = 45.0f;
}

void Camera::Update()
{
    this->m_Projection = glm::perspective(glm::radians(m_Fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    this->m_View = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}
