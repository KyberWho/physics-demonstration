#include "Camera.h"

void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 frontVector{0.0f};
	frontVector.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	frontVector.y = sin(glm::radians(m_Pitch));
	frontVector.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(frontVector);
	
	// Re-calculates the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: m_Front(CAM_FRONT), m_MovementSpeed(CAMERA_SPEED), m_MouseSensitivity(0.1f), m_Zoom(45.0f)
{
	m_Position = position;
	m_WorldUp = up;
	m_Yaw = yaw;
	m_Pitch = pitch;
	UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	m_Position = glm::vec3(posX, posY, posZ);
	m_WorldUp = glm::vec3(upX, upY, upZ);
	m_Yaw = yaw;
	m_Pitch = pitch;
	UpdateCameraVectors();
}

void Camera::ProcessKeyboard(MovementDirection direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;

	if (direction == FORWARD)
		m_Position += m_Front * velocity;
	if (direction == BACKWARD)
		m_Position -= m_Front * velocity;
	if (direction == LEFT)
		m_Position -= m_Right * velocity;
	if (direction == RIGHT)
		m_Position += m_Right * velocity;
}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_Pitch > 89.0f) { m_Pitch = 89.0f; }

	if (m_Pitch < -89.0f) { m_Pitch = -89.0f; }

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}
