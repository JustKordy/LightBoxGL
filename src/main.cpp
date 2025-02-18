#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Logger/Logger.h"
#include "Shader/Shader.h"
#include "Camera/Camera.h"
#include "Utils/Utils.h"


void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
std::string getResourcePath(const std::string &filename);

static float smileB = 0.1;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camera* cam = new Camera();
int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_FALSE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions   
    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    glViewport(0, 0, viewportWidth, viewportHeight);

    glEnable(GL_DEPTH_TEST);

   

    Shader lightningShader(getResourcePath("shaders/basicLightning.vert").c_str(), getResourcePath("shaders/basicLightning.frag").c_str());
   

    // Set up vertex data (and buffer(s)) and attribute pointers
    // We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,   
         0.5f,  0.5f, -0.5f,   
         0.5f,  0.5f, -0.5f,   
        -0.5f,  0.5f, -0.5f,   
        -0.5f, -0.5f, -0.5f,   

        -0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
    
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
    
         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 
    
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 
    
        -0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f, 
    };

    float triVert[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVert), triVert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);





   Logger::Log(sizeof(vertices) / (sizeof(float) * 3));


   
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        Utils::SetDeltaTime(deltaTime);
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       lightningShader.use();

       glm::mat4 projection = glm::mat4(1.0f);
       projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

       glm::mat4 view = glm::mat4(1.0f);
       view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.f)); 
      
       glm::mat4 model = glm::mat4(1.0f);
       model = glm::rotate(model, glm::radians((float)glfwGetTime() * 80), glm::vec3(1.0f, 1.0f, 1.0f)); 

       //glm::vec4 colors = glm::vec4((float)sin(glfwGetTime() * 2), (float)sin(glfwGetTime() * 3), (float)sin(glfwGetTime() * 3), 1.f);

       glm::vec4 colors= glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
       lightningShader.setMat4("view", view);
       lightningShader.setMat4("projection", projection);
       lightningShader.setMat4("model", model);
       lightningShader.setVec4("u_Colors", colors);

       glBindVertexArray(VAO);
       glDrawArrays(GL_TRIANGLES, 0, 3);   

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);  
}

std::string getResourcePath(const std::string &filename)
{
    return std::string(PROJECT_ROOT_DIR) + "/resources/" + filename;
    Logger::Log(PROJECT_ROOT_DIR);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    cam->HandleLook(xposIn, yposIn, Utils::isMouseClicked());
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Utils::SetMouseClicked(true);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        Utils::SetMouseClicked(false);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    cam->HandleZoom(yoffset);
}