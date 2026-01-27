#pragma once

#include <glad/gl.h>

#include "Logger.h"

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