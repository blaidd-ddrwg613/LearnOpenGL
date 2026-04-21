#pragma once

#include <iostream>

#include "stb_image/stb_image.h"
#include "glad/glad.h"
#include "Shader.h"

class Texture
{
public:
    unsigned int ID;
    // Relative Texture Path resources/textures/
    std::string TexturePath = std::string(RESOURCES_PATH) + "textures/";

    Texture(const char* image, GLenum slot);

    // Assigns a texture unit to a texture
    void texUnit(Shader& shader, const char* uniform, GLuint unit);

    // Binds a texture
    void Bind();

    // Unbinds a texture
    void Unbind();

    // Deletes a texture
    void Delete();
};
