#include "Mesh.h"

// ---------------------------------------------------------------------
// CUBE MESH
// ---------------------------------------------------------------------

// Updates BoxMesh's position/rotation/scale when called
void Mesh::UpdateModelMatrix()
{
    m_ModelMatrix = glm::mat4(1.0f); // Prevents basis vectors from being modified and ruining model matrix
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));
    m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
}

// ---------------------------------------------------------------------
// BOX MESH
// ---------------------------------------------------------------------

// Creates a simple cube mesh foundation
BoxMesh::BoxMesh(Texture* texture)
	: m_Texture(texture)
{
    // Simple cube vertices: x, y, z, u, v
    float vertices[] = {
        // Front face
        -0.5f,-0.5f, 0.5f,  0.0f,0.0f,
         0.5f,-0.5f, 0.5f,  1.0f,0.0f,
         0.5f, 0.5f, 0.5f,  1.0f,1.0f,
        -0.5f, 0.5f, 0.5f,  0.0f,1.0f,

        // Back face
        -0.5f,-0.5f,-0.5f,  1.0f,0.0f,
         0.5f,-0.5f,-0.5f,  0.0f,0.0f,
         0.5f, 0.5f,-0.5f,  0.0f,1.0f,
        -0.5f, 0.5f,-0.5f,  1.0f,1.0f,

        // Left face
        -0.5f,-0.5f,-0.5f,  0.0f,0.0f,
        -0.5f,-0.5f, 0.5f,  1.0f,0.0f,
        -0.5f, 0.5f, 0.5f,  1.0f,1.0f,
        -0.5f, 0.5f,-0.5f,  0.0f,1.0f,

        // Right face
         0.5f,-0.5f,-0.5f,  1.0f,0.0f,
         0.5f,-0.5f, 0.5f,  0.0f,0.0f,
         0.5f, 0.5f, 0.5f,  0.0f,1.0f,
         0.5f, 0.5f,-0.5f,  1.0f,1.0f,

         // Top face
         -0.5f, 0.5f,-0.5f,  0.0f,1.0f,
          0.5f, 0.5f,-0.5f,  1.0f,1.0f,
          0.5f, 0.5f, 0.5f,  1.0f,0.0f,
         -0.5f, 0.5f, 0.5f,  0.0f,0.0f,

         // Bottom face
         -0.5f,-0.5f,-0.5f,  0.0f,1.0f,
          0.5f,-0.5f,-0.5f,  1.0f,1.0f,
          0.5f,-0.5f, 0.5f,  1.0f,0.0f,
         -0.5f,-0.5f, 0.5f,  0.0f,0.0f,
    };

    unsigned int indices[] = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        8,9,10, 10,11,8,
        12,13,14, 14,15,12,
        16,17,18, 18,19,16,
        20,21,22, 22,23,20
    };

    m_IndexCount = sizeof(indices) / sizeof(unsigned int);

    m_VAO = new VertexArray();
    m_VBO = new VertexBuffer(vertices, sizeof(vertices));
    m_IBO = new IndexBuffer(indices, m_IndexCount);

    VertexBufferLayout layout;
    layout.Push<float>(3); // position
    layout.Push<float>(2); // tex coords

    m_VAO->AddBuffer(*m_VBO, layout);

    m_VAO->Bind();
    m_IBO->Bind();
}

BoxMesh::~BoxMesh()
{
    delete m_VAO;
	delete m_VBO;
	delete m_IBO;
}

// Draws a simple cube mesh (we need to pass in view matrix and projection matrix)
void BoxMesh::Draw(ShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const
{
    shader.Bind();
    glm::mat4 mvp = projectionMatrix * viewMatrix * this->GetModelMatrix();

    shader.SetUniformMat4f("u_MVP", mvp);

    if (m_Texture)
    {
        m_Texture->Bind(0);
        shader.SetUniform1i("u_Texture", 0);
    }

    GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr));
}
