// Controls the flow of rendering operations, including initialization, clearing the screen, and drawing objects. 
// It provides an interface for managing the rendering process and interacts with shaders and textures to produce the final output on the screen.
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Logger.h"

//#include "Buffer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

// -------------------------------------------------------------------------------
// FORWARD DECLARATIONS
// -------------------------------------------------------------------------------

class VertexBuffer;
class VertexArray;
class IndexBuffer;

class VertexBufferLayout;

class ShaderProgram;
class Texture;

// -------------------------------------------------------------------------------
// RENDERER CLASS
// -------------------------------------------------------------------------------

// Virtual class used as a base for specific renderers (e.g. texture renderer, sprite renderer, etc.) that will implement the actual drawing logic for different types of objects.
class Renderer
{
	public:
		Renderer();
		~Renderer();

		virtual void Init();
		void Draw() const;
};

// --------------------------------------------------------------------------------
// MESH RENDERER CLASS
// --------------------------------------------------------------------------------

class MeshRenderer : public Renderer
{
	private:
		glm::mat4 m_ProjectionMatrix;

		ShaderProgram* m_Shader;
	public:
		MeshRenderer();
		~MeshRenderer();

		void Init(unsigned int screenWidth, unsigned int screenHeight);
		void DrawCubeMesh(BoxMesh* currentMesh, glm::mat4 viewMatrix, unsigned int screenWidth, unsigned int screenHeight); // MAKE THIS MORE GENERAL IN THE FUTURE TO ACCEPT ANY MESH
};

// -------------------------------------------------------------------------------
// TEXTURE RENDERER CLASS
// -------------------------------------------------------------------------------

class TextureRenderer : public Renderer
{
	private:
		glm::mat4 m_ProjectionMatrix;

		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;

		ShaderProgram* m_Shader;
	public:
		TextureRenderer();
		~TextureRenderer();

		void Init(unsigned int screenWidth, unsigned int screenHeight);
		void Draw(const Texture* texture, float* textureParameters);
};