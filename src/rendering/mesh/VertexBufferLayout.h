#pragma once

#include <glad/gl.h>
#include <vector>

#include "Logger.h"

// -------------------------------------------------------------------------------
// VERTEX BUFFER ELEMENT
// -------------------------------------------------------------------------------

// Defines an actual vertex
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalised;

	// Returns the size of the type in bytes
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:         return sizeof(float);
		case GL_UNSIGNED_INT:  return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
		}
		ASSERT(false); // Unknown type
		return 0; // Should never reach here
	}
};

// -------------------------------------------------------------------------------
// VERTEX BUFFER LAYOUT CLASS
// -------------------------------------------------------------------------------

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements; // Contains the structure of the vertex buffer
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {
	}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false, "Unexpected Type!"); // This will throw error if not one of the specializations below
	}

	template<>
	void Push<float>(unsigned int count)
	{
		VertexBufferElement element = { GL_FLOAT, count, GL_FALSE };

		m_Elements.push_back(element);
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		VertexBufferElement element = { GL_UNSIGNED_INT, count, GL_FALSE };

		m_Elements.push_back(element);
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		VertexBufferElement element = { GL_UNSIGNED_BYTE, count, GL_TRUE };

		m_Elements.push_back(element);
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;

	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }
};