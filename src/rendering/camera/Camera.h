// This module handles camera movement/rotation based on user input.
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Logger.h"

// -------------------------------------------------------------------------------
// CAMERA CLASS
// -------------------------------------------------------------------------------

// TODO: ADD ZOOM FUNCTIONALITY + REWRITE TO BE FLEXIBLE WITH MY CODEBASE

enum MovementDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Rewrite this later PLEASE 
const float CAMERA_SPEED = 20.0f;

const glm::vec3 CAM_POSITION = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 CAM_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 CAM_UP = glm::vec3(0.0f, 1.0f, 0.0f);

const float CAM_YAW = -90.0f;
const float CAM_PITCH = 0.0f;


class Camera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	glm::vec3 m_WorldUp;

	float m_Yaw;
	float m_Pitch;

	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

	void UpdateCameraVectors();
public:

	// Constructors with vectors (1) and scalar values (2)
	Camera(glm::vec3 position = CAM_POSITION, glm::vec3 up = CAM_UP, float yaw = CAM_YAW, float pitch = CAM_PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	void ProcessKeyboard(MovementDirection direction, float deltaTime);
	void ProcessMouse(float xoffset, float yoffset);

	glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_Front, m_Up); };
};