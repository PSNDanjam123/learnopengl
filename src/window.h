#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Window {
    // Constants
    extern const unsigned int SCR_WIDTH;
    extern const unsigned int SCR_HEIGHT;

    // Variables
    extern float lastX, lastY, deltaTime, lastFrame;
    extern bool firstMouse;

    // Functions
    GLFWwindow* init(const std::string &title);
    extern void updateDeltaTime();
    extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); 
    extern void processInput(GLFWwindow* window);
}
