#include "Texture.h"

Texture::Texture(const char* image) : texShader("default.vert", "default.frag")
{
	// Build the actual image path.
	std::string imagePath = TexturePath + std::string(image);

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(imagePath.c_str(), &widthImg, &heightImg, &numColCh, 0);
	int imageFormat = GL_RGBA;
	switch (numColCh)
	{
		case 3:
			imageFormat = GL_RGB;
			break;

		case 4:
			imageFormat = GL_RGBA;
	}

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, widthImg, heightImg, 0, imageFormat, GL_UNSIGNED_BYTE, bytes);
	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);
	texUnit(texShader, "ourTexture", 0);
}

int Texture::SetShader(Shader shader)
{
	if (shader.ID != 0)
	{
		texShader = shader;
		texUnit(texShader, "ourTexture", 0);
		return 0;
	} else
	{
		std::cout << "ERROR::Must Use A valid Shader" << std::endl;
		return -1;
	}
}

int Texture::SetTexturePath(std::string path)
{
	if (!path.empty())
	{
		TexturePath = std::string(RESOURCES_PATH) + path;
		return 0;
	}
	else
	{
		std::cout << "ERROR::INVALID TEXTURE PATH" << std::endl;
		return -1;
	}
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.use();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
