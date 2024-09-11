#pragma once
#include <glad/glad.h>
#include <opengl/VAO.h>
#include <opengl/VBO.h>
#include <opengl/EBO.h>
#include <opengl/Texture.h>

class Sprite
{
public:
	Sprite() = default;
	Sprite(Geometry&& geometry, const char* texturePath)
		: m_geometry(new Geometry(geometry))
	{
		vao_create(vao);
		vbo_create(vbo);
		ebo_create(ebo);

		vao_bind(vao);
		vbo_buffer(vbo, m_geometry->vertices);
		ebo_buffer(ebo, m_geometry->indices);

		vao_attr(vao, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
		vao_attr(vao, 1, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex));

		texture_create(texture, texturePath);
	}

	void setData(Geometry&& geometry, const char* texturePath)
	{
		m_geometry = new Geometry(geometry);
		vao_create(vao);
		vbo_create(vbo);
		ebo_create(ebo);

		vao_bind(vao);
		vbo_buffer(vbo, m_geometry->vertices);
		ebo_buffer(ebo, m_geometry->indices);

		vao_attr(vao, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
		vao_attr(vao, 1, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex));

		texture_create(texture, texturePath);
	}

	void update()
	{
		vao_bind(vao);
		vbo_update_buffer(vbo, m_geometry->vertices);
	}
	
	void draw()
	{
		vao_bind(vao);
		texture_bind(texture);
		glDrawElements(GL_TRIANGLES, m_geometry->indices.size(), GL_UNSIGNED_INT, 0);
	}

	Geometry* m_geometry;
private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	Texture texture;
};