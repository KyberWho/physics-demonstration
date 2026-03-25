#pragma once

// This module is the base class for all shapes in the physics engine. It will be used to represent the shape of an object in the physics engine
// as well as to calculate the collision response of the object.

#include "Logger.h"
#include "glm/glm.hpp"

enum ShapeType
{
	SHAPE_BOX, // only one for now, but we can add more shapes in the future (e.g. sphere, capsule, etc.)
};

class Shape
{
	private:
		glm::vec3 m_Position{ 0.0f };
		glm::vec3 m_Rotation{ 0.0f };
		glm::vec3 m_Scale{ 1.0f }; 
	public:
		Shape() {};
		~Shape() {};
		
		virtual ShapeType GetType() const = 0;

		// shape functions here
		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec3 GetRotation() const { return m_Rotation; }
		glm::vec3 GetScale() const { return m_Scale; }

		void SetScale(glm::vec3 scale) { m_Scale = scale; }
};