#pragma once
// This module is the rigid body class, which will be used to represent the physical properties of an object in the physics engine. 
// It will be used to store the mass, velocity, and other properties of the object, as well as to apply forces to the object.

#include "Logger.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Box.h"

class RigidBody
{
	private:
		Shape* m_Shape; // The shape of the rigid body, used to calculate the collision response of the rigid body

		// Inverse Mass is used to calculate the acceleration of the rigid body, and is also used to calculate the collision response of the rigid body. 
		// It is stored as a separate variable to avoid division by zero when calculating the acceleration of the rigid body
		// (if mass is zero, then the rigid body is immovable, and therefore has infinite mass, which would cause a division by zero error when calculating the acceleration of the rigid body).
		float m_Mass, m_InvMass; 
		
		glm::vec3 m_Position{ 0.0f };
		glm::quat m_Orientation{ 1, 0, 0, 0 };

		glm::vec3 m_Velocity{ 0.0f };
		glm::vec3 m_AngularVelocity{ 0.0f };

		glm::vec3 m_CurrentForces{ 0.0f }; // All forces acting on the rigid body will be stored here, used to calculate acceleration later on
		glm::vec3 m_CurrentTorque{ 0.0f }; // All torques acting on the rigid body will be stored here, used to calculate angular acceleration later on
	public:
		RigidBody(Shape* givenShape, float mass);
		~RigidBody();
		
		void Update(float dt);

		void AddForce(const glm::vec3& force);
		void ClearActingForces();

		void AddTorque(const glm::vec3& torque);
		void ClearActingTorques();
		
		float GetMass() const { return m_Mass; }
		bool HasMass() const { return m_Mass > 0.0f; }

		glm::vec3 GetPosition() const { return m_Position; }
		glm::quat GetOrientation() const { return m_Orientation; }
};