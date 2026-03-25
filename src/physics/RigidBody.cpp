#include "RigidBody.h"

// TODO: add bounding shape and collision detection 

RigidBody::RigidBody(Shape* givenShape, float mass)
	: m_Shape(givenShape), m_Mass(mass)
{
	m_InvMass = (mass > 0.0f) ? 1.0f / mass : 0.0f; // If mass is zero, then the rigid body is immovable (static)
}

RigidBody::~RigidBody()
{
    delete m_Shape;
}



// Angular motion (simplified, assuming a constant inertia tensor for now)
//glm::mat3 invInertiaTensor; // Placeholder inertia tensor, to be calculated based on shape and mass    
//   switch (m_Shape->GetType())
//   {
//       case SHAPE_BOX:
//           {
//               Box* boxShape = static_cast<Box*>(m_Shape);
//               glm::mat3 inertia = boxShape->ComputeInertiaTensor(m_Mass);
//               invInertiaTensor = glm::inverse(inertia);
   //			
//               delete boxShape; 
//           }
//           break;
//       default:
//           LOG_WARN("Unsupported shape type for inertia tensor calculation!");
   //		break;
//   }

void RigidBody::Update(float dt)
{
    if (m_InvMass == 0.0f)
        return; // static body

    // Linear motion
    glm::vec3 acceleration = m_CurrentForces * m_InvMass;
    m_Velocity += acceleration * dt;
    m_Position += m_Velocity * dt;
    LOG_INFO("(" << m_Position.x << "," << m_Position.y << "," << m_Position.z << ")")

    // Angular motion
    glm::vec3 angularAcceleration = m_CurrentTorque;
    m_AngularVelocity += angularAcceleration * dt;

    glm::quat deltaRotation = glm::quat(0,
        m_AngularVelocity.x,
        m_AngularVelocity.y,
        m_AngularVelocity.z
    ) * m_Orientation;

    m_Orientation += 0.5f * deltaRotation * dt;
    m_Orientation = glm::normalize(m_Orientation);

    // Clear forces
    m_CurrentForces = glm::vec3(0.0f);
    m_CurrentTorque = glm::vec3(0.0f);
}

void RigidBody::AddForce(const glm::vec3& force)
{
	m_CurrentForces += force;
}

void RigidBody::ClearActingForces()
{
	m_CurrentForces = glm::vec3(0.0f);
}

void RigidBody::AddTorque(const glm::vec3& torque)
{
    m_CurrentTorque += torque;
}

void RigidBody::ClearActingTorques()
{
	m_CurrentTorque = glm::vec3(0.0f);
}
