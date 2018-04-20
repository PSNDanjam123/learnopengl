#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Texture {
    GLuint load(const std::string &path, GLint format, GLint wrap, GLint filter);
    void activate(GLuint id, GLenum texture);
}
