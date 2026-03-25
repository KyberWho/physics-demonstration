#include "Entity.h"

Entity::Entity(Mesh* mesh, RigidBody* rigidBody)
	: m_Mesh(mesh), m_RigidBody(rigidBody)
{

}

Entity::~Entity()
{
}

// Syncs the position and rotation of the mesh with the position and rotation of the rigid body (called every frame in the main loop after the physics engine step)
void Entity::Sync()
{
	glm::mat4 m_ModelMatrix = glm::translate(glm::mat4(1.0f), 
		m_RigidBody->GetPosition()) * glm::mat4_cast(m_RigidBody->GetOrientation());

	m_Mesh->SetModelMatrix(m_ModelMatrix);
}