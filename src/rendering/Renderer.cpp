#include "Renderer.h"

#include "VertexBufferLayout.h"

// -------------------------------------------------------------------------------
// RENDERER CLASS
// -------------------------------------------------------------------------------

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

// Enables blending for transparency
void Renderer::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Draw() const
{
}

// --------------------------------------------------------------------------------
// MESH RENDERER CLASS (make a singleton class that handles all mesh rendering)
// --------------------------------------------------------------------------------

MeshRenderer::MeshRenderer()
	: m_Shader(0), m_ProjectionMatrix(0)
{

}

MeshRenderer::~MeshRenderer() 
{
    delete m_Shader;
	m_Shader = nullptr;
}

void MeshRenderer::Init(unsigned int screenWidth, unsigned int screenHeight)
{
    m_ProjectionMatrix = glm::perspective(
        glm::radians(45.0f), screenWidth / (float) screenHeight,
        0.1f, 100.0f
	);

	m_Shader = new ShaderProgram("assets/shaders/test3D.shader");
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0);
}


void MeshRenderer::DrawCubeMesh(BoxMesh* currentMesh, glm::mat4 viewMatrix, unsigned int screenWidth, unsigned int screenHeight)
{
    m_ProjectionMatrix = glm::perspective(
        glm::radians(45.0f), screenWidth / (float) screenHeight,
        0.1f, 100.0f
    );

	currentMesh->Draw(*m_Shader, viewMatrix, m_ProjectionMatrix);
}


// --------------------------------------------------------------------------------
// TEXTURE RENDERER CLASS
// --------------------------------------------------------------------------------

TextureRenderer::TextureRenderer()
    : m_IBO(0), m_VBO(0), m_VAO(0)
{
    m_Shader = 0;
    m_ProjectionMatrix = 0;
}

// ASSUMING THEY ARE NOT 0, NEED TO REFACTOR TO CHECK THIS
TextureRenderer::~TextureRenderer()
{
    if (m_VAO) { delete m_VAO; m_VAO = nullptr; }
    if (m_VBO) { delete m_VBO; m_VBO = nullptr; }
    if (m_IBO) { delete m_IBO; m_IBO = nullptr; }
    if (m_Shader) { delete m_Shader; m_Shader = nullptr; }
}

void TextureRenderer::Init(unsigned int screenWidth, unsigned int screenHeight)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_ProjectionMatrix = glm::ortho(
        0.0f, (float)screenWidth, 
        0.0f, (float)screenHeight,
        -1.0f, 1.0f
    );

    float vertices[] = {
        // position    // tex coords
        -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,   0.0f, 1.0f
    };
    
	// Reduces GPU memory bandwidth usage by reusing shared vertices for indexed drawing
    unsigned int indices[] = { 
        0,1,2, 
        2,3,0 
    };

	m_VAO = new VertexArray();
    m_VBO = new VertexBuffer(vertices, sizeof(vertices));
    
    VertexBufferLayout layout;
	layout.Push<float>(2); // position
	layout.Push<float>(2); // texture coordinates
    m_VAO->AddBuffer(*m_VBO, layout);

    m_IBO = new IndexBuffer(indices, 6);

	float defaultColour[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Default color (gray)

	m_Shader = new ShaderProgram("assets/shaders/test.shader");
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0); // Set the texture uniform to use texture slot 0
}

void TextureRenderer::Draw(const Texture* texture, float* textureParameters)
{
    m_Shader->Bind();

	glm::mat4 model = glm::mat4(1.0f); // Identity matrix for model transformation

    model = glm::translate(model, glm::vec3(textureParameters[0] + textureParameters[2] * 0.5f, textureParameters[1] + textureParameters[3] * 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(textureParameters[2], textureParameters[3], 1.0f));

    m_Shader->SetUniformMat4f("u_Model", model); // Set the MVP matrix uniform
    m_Shader->SetUniformMat4f("u_Projection", m_ProjectionMatrix); // Set the MVP matrix uniform


    m_VAO->Bind();
    m_IBO->Bind();
    texture->Bind();
    
    // Update shader uniforms based on the provided texture parameters
    m_Shader->SetUniform1i("u_Texture", 0); // Set the texture uniform to use texture slot 0

    GLCall(glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr));
}