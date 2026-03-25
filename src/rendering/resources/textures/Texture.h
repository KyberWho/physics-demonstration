#pragma once

// TODO: REFACTOR THIS TO WORK WITH TEXTURES UNDER MATERIALS FOR BETTER ORGANIZATION (TO DO IN FUTURE ITERATIONS)

#include <glad/gl.h>

#include "Logger.h"

// -------------------------------------------------------------------------------
// TEXTURE CLASS
// -------------------------------------------------------------------------------

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;

	unsigned char* m_LocalBuffer; // Pointer to the image data in local memory
	int m_width, m_height, m_BPP; // Width, height, and bits per pixel of the texture

public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0) const; // Bind the texture to an optional slot
	void Unbind() const; // Unbind the texture

	inline int GetWidth() const { return m_width; } // Get the width of the texture
	inline int GetHeight() const { return m_height; } // Get the height of the texture
};