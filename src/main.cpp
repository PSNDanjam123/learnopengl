// definitions
#define STB_IMAGE_IMPLEMENTATION // Needed for stb_image.h to work

// system includes
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// local includes
#include "./window.h"   // GLFW window code
#include "./shader.h"   // Loading and compiling shader code
#include "./camera.h"   // Camera object
#include "./cube.h"     // Cube code

//camera
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

//Cubes
unsigned int cubeVAO, cubeVBO, lampVAO, lampVBO;

int main()
{
    GLFWwindow* window = Window::init("Learn OpenGL");

    // Init shaders
    Shader lightingShader("../src/shaders/lightingShader.vs", "../src/shaders/lightingShader.fs"); 
    Shader lampShader("../src/shaders/lampShader.vs", "../src/shaders/lampShader.fs");

    // Create cubes
    Cube::createCube(cubeVAO, cubeVBO, 0);
    Cube::createCube(lampVAO, lampVBO, 0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // setup game loop
    while (!glfwWindowShouldClose(window))
    {
        // update Delta time
        Window::updateDeltaTime();

        // process inputs
        Window::processInput(window);

        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw cube ---------------------------------------
        
        // Set shader
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        // Setup camera
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Window::SCR_WIDTH / (float)Window::SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);

        // Setup Cube
        glBindVertexArray(cubeVAO);
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::mat4 model;
        model = glm::translate(model, pos);
        lightingShader.setMat4("model", model);

        // Draw Shape
        glDrawArrays(GL_TRIANGLES, 0, Cube::vertCount);

        // Draw lamp -------------------------------------
        
        // Set shader
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);

        // Setup Lamp
        glBindVertexArray(lampVAO);
        pos = glm::vec3(1.2f, 1.0f, 2.0f);
        model = glm::translate(glm::mat4(), pos);
        model = glm::scale(model, glm::vec3(0.2f));
        lampShader.setMat4("model", model);

        // Draw Shape
        glDrawArrays(GL_TRIANGLES, 0, Cube::vertCount);

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
