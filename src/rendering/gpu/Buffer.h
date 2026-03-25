#pragma once

#include <glad/gl.h>

#include "Logger.h"

class VertexBufferLayout; // Forward declaration to avoid circular dependency within the files

// -------------------------------------------------------------------------------
// VERTEX BUFFER CLASS
// -------------------------------------------------------------------------------

// Encapsulates an OpenGL vertex buffer object (dedicated memory area for vertex data - e.g. positions, texture coordinates, normals, etc.)
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, unsigned int size);
};

// -------------------------------------------------------------------------------
// VERTEX ARRAY CLASS
// -------------------------------------------------------------------------------

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

// -------------------------------------------------------------------------------
// INDEX BUFFER CLASS
// -------------------------------------------------------------------------------

// Stores vertex indices for indexed drawing (reusing shared vertices + reducing GPU memory bandwidth usage)
class IndexBuffer
{
private:
	unsigned int m_RendererID; // Unique ID for the VBO
	unsigned int m_Count; // Number of indices in the buffer
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	// Get the number of indices in the buffer
	inline unsigned int GetCount() const { return m_Count; }
};

