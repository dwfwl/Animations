#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

struct VAO
{
	uint32_t handle;
};

void vao_create(VAO& self)
{
	glGenVertexArrays(1, &self.handle);
}

void vao_bind(VAO& self)
{
	glBindVertexArray(self.handle);
}

void vao_attr(VAO& self, int index, uint32_t size, GLenum type, GLsizei stride, size_t offset)
{
	vao_bind(self);
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}

void vao_unbind(VAO& self)
{
	glBindVertexArray(0);
}

void vao_delete(VAO& self)
{
	glDeleteVertexArrays(1, &self.handle);
}