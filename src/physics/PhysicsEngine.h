#pragma once
// This module is responsible for handling the actual simulation of the physics (right now, I am only planning to add rigid body compatability,
// but in future iteration, I will add more scenes).
#include <vector>

#include "Logger.h"

#include "RigidBody.h"

// ------------------------------------------------------------------
// PHYSICS ENGINE
// ------------------------------------------------------------------

const float GRAVITY = -9.81f;

class PhysicsEngine
{
	private:
		// rigid body handler here
		static const float timeStep; // fixed time step for physics simulation (60 FPS)

		static std::vector<RigidBody*> m_RigidBodies; // all rigid bodies in the scene will be stored here (deleted when the physics engine is destroyed)
	public:
		PhysicsEngine() = delete;
		~PhysicsEngine() = delete;

		static void Shutdown();

		static void AddRigidBody(RigidBody* body) { m_RigidBodies.push_back(body); }
		static void Init();
		static void Step();
};