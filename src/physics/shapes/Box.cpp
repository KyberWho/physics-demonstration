#include "Box.h"

// Refactor this later
Box::Box(glm::vec3 halfExtents, glm::vec3 scale)
	: m_HalfExtents(halfExtents)
{
	SetScale(scale);
}

Box::~Box()
{
}

glm::mat3 Box::ComputeInertiaTensor(float mass) const
{
    float width = (m_HalfExtents.x * 2.0f) * GetScale().x;
    float height = (m_HalfExtents.y * 2.0f) * GetScale().y;
    float depth = (m_HalfExtents.z * 2.0f) * GetScale().z;

    float ix = (1.0f / 12.0f) * mass * (height * height + depth * depth);
    float iy = (1.0f / 12.0f) * mass * (width * width + depth * depth);
    float iz = (1.0f / 12.0f) * mass * (width * width + height * height);

    glm::mat3 inertia(1.0f);
    inertia[0][0] = ix;
    inertia[1][1] = iy;
    inertia[2][2] = iz;

    return inertia;
}
