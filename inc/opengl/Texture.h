#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <memory>

struct Texture
{
	unsigned int handle;
	unsigned char* data;
	std::string type;
};

inline bool texture_create(Texture& self, const char* file)
{
	int width, height, nrChannels;
	self.data = stbi_load(file, &width, &height, &nrChannels, 0);

	glGenTextures(1, &self.handle);
	glBindTexture(GL_TEXTURE_2D, self.handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (!self.data)
	{
		std::cout << "TEXTURE ERR :: include/gfx/texture.h\nFailed to load image to `data`" << std::endl;
		return false;
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, self.data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return true;
	}
}

inline void texture_bind(Texture& self)
{
	glBindTexture(GL_TEXTURE_2D, self.handle);
}

inline void texture_unbind(Texture& self)
{
	glBindTexture(0, self.handle);
}

inline void texture_delete(Texture& self)
{
	glDeleteTextures(1, &self.handle);
}