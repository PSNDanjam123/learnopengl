#include "./cube.h"

#include <glad/glad.h>

std::size_t Cube::vertSize = 8 * sizeof(float);

std::vector<float> Cube::vertices = {
    //Position			  //Texture     //Normal
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f
};

std::size_t Cube::vertCount = Cube::vertices.size();
std::size_t Cube::cubeSize = Cube::vertCount * sizeof(float);

void Cube::createCube(unsigned int &VAO, unsigned int &VBO, const unsigned int &posAttribPointer) {
    // Generate the objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    //Bind the objects
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Load the vertex data
    glBufferData(GL_ARRAY_BUFFER, Cube::cubeSize, &Cube::vertices[0], GL_STATIC_DRAW);

    //Set the attribute pointer for position data and enable it
    glVertexAttribPointer(posAttribPointer, 3, GL_FLOAT, GL_FALSE, Cube::vertSize, (void*)0);
    glEnableVertexAttribArray(posAttribPointer);

    //Unbind the VAO
    glBindVertexArray(0);
}

void Cube::bindNormals(unsigned int &VAO, unsigned int &VBO, const unsigned int &normAttribPointer) {
    //Bin the objects
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Set the attribute pointer for the normal data and enable it
    glVertexAttribPointer(normAttribPointer, 3, GL_FLOAT, GL_FALSE, Cube::vertSize, (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(normAttribPointer);

    //unbind the VAO
    glBindVertexArray(0);
}
