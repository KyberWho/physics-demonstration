#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout; // Forward declaration to avoid circular dependency within the files

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