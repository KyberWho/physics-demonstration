#include "PhysicsEngine.h"

const float PhysicsEngine::timeStep = 1.0f / 60.0f; // fixed time step for physics simulation (60 FPS)
std::vector<RigidBody*> PhysicsEngine::m_RigidBodies;

void PhysicsEngine::Shutdown()
{
	if (m_RigidBodies.empty())
		return;

	for (RigidBody* body : m_RigidBodies)
	{
		delete body;
	}
}

void PhysicsEngine::Init()
{
	LOG_INFO("Initializing physics engine...");

	LOG_INFO("Physics engine initialized successfully!");
}

void PhysicsEngine::Step()
{
	for (RigidBody* body : m_RigidBodies)
	{
		if (body->HasMass())
		{
			// Apply gravity to all bodies with mass
			body->AddForce(glm::vec3(0.0f, GRAVITY * body->GetMass(), 0.0f));
		}

		body->Update(timeStep);
	}
}
