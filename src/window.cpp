#include "./window.h"
#include "./camera.h"
#include <stdexcept>

const unsigned int Window::SCR_WIDTH = 200,
      Window::SCR_HEIGHT = 150;

float Window::lastX = Window::SCR_WIDTH / 2.0f,
      Window::lastY = Window::SCR_HEIGHT / 2.0f,
      Window::deltaTime = 0.0f,
      Window::lastFrame = 0.0f;

bool Window::firstMouse = true;

GLFWwindow* Window::init(const std::string &title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(Window::SCR_WIDTH, Window::SCR_HEIGHT, title.c_str(), NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw new std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, Window::mouse_callback);
    glfwSetScrollCallback(window, Window::scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw new std::runtime_error("Failed to initialize GLAD");
    }

    return window;
}

void Window::framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::mouse_callback(GLFWwindow*, double xpos, double ypos) {
    if(Window::firstMouse) {
        Window::lastX = xpos;
        Window::lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Window::scroll_callback(GLFWwindow*, double, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

void Window::processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void Window::updateDeltaTime() {
    float currentFrame = glfwGetTime();
    Window::deltaTime = currentFrame - Window::lastFrame;
    Window::lastFrame = currentFrame;
}
