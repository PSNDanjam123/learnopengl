#pragma once

#include <vector>

/**
 * Vertices code to keep main.cpp clean
 */

namespace Cube {
    extern std::size_t vertSize;    // Size of single vertex e.g: 5 * sizeof(float)
    extern std::size_t vertCount;   // Number of vertices e.g: 36
    extern std::size_t cubeSize;    // Size of the vertices array e.g: vertices.size() * sizeof(float)
    extern std::vector<float> vertices; // Array of all the vertices information
    extern void createCube(unsigned int &VAO, unsigned int &VBO, const unsigned int &posAttribPointer); // Quickly bind a cube to OpenGL and set buffer data
    extern void bindNormals(unsigned int &VAO, unsigned int &VBO, const unsigned int &normAttribPointer);
}
