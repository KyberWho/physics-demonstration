#pragma once

#include "Shape.h"

// This module is the box shape, which will be used to represent a box in the physics engine. It will be used to calculate the collision response of the cube.

class Box : public Shape
{
	private:
		glm::vec3 m_HalfExtents{ 0.5f }; // Half-size in each dimension for collision calculations (default is a unit cube)
	public:
		Box(glm::vec3 halfExtents, glm::vec3 scale);
		~Box();
		
		glm::mat3 ComputeInertiaTensor(float mass) const;

		ShapeType GetType() const override { return SHAPE_BOX; }
		glm::vec3 GetHalfExtents() const { return m_HalfExtents; }
};