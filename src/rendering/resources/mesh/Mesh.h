#pragma once

#include <vector>

#include "Buffer.h"
#include "VertexBufferLayout.h"

#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//// Defines the structure of a vertex (position, texture coordinates)
//struct Vertex
//{
//	float m_Position[3];
//	float m_TexCoords[2];
//};

// Encapsulates a mesh (collection of vertices and indices) for rendering 
class Mesh
{
	private:
		void UpdateModelMatrix();

		glm::mat4 m_ModelMatrix{ 1.0f };

		glm::vec3 m_Position{ 0.0f };
		glm::vec3 m_Rotation{ 0.0f };
		glm::vec3 m_Scale{ 1.0f };
	public:
		Mesh() = default;

		virtual void Draw(ShaderProgram& shader, glm::mat4 projectionMatrix, glm::mat4 modelMatrix = glm::mat4(0)) const = 0;

		void SetPosition(const glm::vec3& position) { m_Position = position; UpdateModelMatrix(); }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; UpdateModelMatrix(); }
		void SetScale(const glm::vec3& scale) { m_Scale = scale; UpdateModelMatrix(); }

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }

		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		void SetModelMatrix(const glm::mat4& modelMatrix) { m_ModelMatrix = modelMatrix; }
};

// Creates a unit box mesh (to be changed later)
class BoxMesh : public Mesh
{
	private:
		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;
		Texture* m_Texture; // to become material later (shader + texture)

		unsigned int m_IndexCount = 0;
	public:
		BoxMesh(Texture* texture);
		~BoxMesh();

		void Draw(ShaderProgram& shader, glm::mat4 projectionMatrix, glm::mat4 modelMatrix = glm::mat4(0)) const override;
};