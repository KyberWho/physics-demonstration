#pragma once

#include <glad/gl.h>

#include "Logger.h"

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