#include "./texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

GLuint Texture::load(const std::string &path, GLint format, GLint wrap, GLint filter) {
    // Gen and bind texture
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // Set wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

    // Set filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    int width, height, nrChannels;

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(!data) {
        throw new std::runtime_error("Failed to load texture");
    }

    // Load texture into OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // free data
    stbi_image_free(data);

    return id;
}

void Texture::activate(GLuint id, GLenum texture) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, id);
}
