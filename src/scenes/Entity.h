#pragma once
// This module is the entity class, which will be used to represent an object in the scene. It will be used to store the components of the object, as well as to update and render the object.

#include "Logger.h"

#include "Mesh.h"
#include "RigidBody.h"

// NEED TO REFACTOR THIS SO THAT CUBEMESH CAN BE REPLACED WITH ANY MESH IN THE FUTURE 

class Entity
{
	private:
		Mesh* m_Mesh;
		RigidBody* m_RigidBody;
	public:
		Entity(Mesh* mesh, RigidBody* RigidBody);
		~Entity();
		
		void Sync();
};