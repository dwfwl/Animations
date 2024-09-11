#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

struct EBO
{
	uint32_t handle;
};

void ebo_create(EBO& self)
{
	glGenBuffers(1, &self.handle);
}

void ebo_bind(const EBO& self)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.handle);
}

void ebo_buffer(const EBO& self, std::vector<uint32_t> indices)
{
	ebo_bind(self);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

void ebo_unbind(const EBO& self)
{
	glBindBuffer(0, self.handle);
}

void ebo_delete(EBO& self)
{
	glDeleteBuffers(1, &self.handle);
}