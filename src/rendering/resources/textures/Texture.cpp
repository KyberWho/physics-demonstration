#include "Texture.h"

#include "stb_image.h"

// -------------------------------------------------------------------------------
// TEXTURE CLASS
// -------------------------------------------------------------------------------

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
	m_width(0), m_height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1); // Flip the image vertically (OpenGL expects images to load from the bottom left so its flipped to top left)
	m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4); // Loads texture data into m_LocalBuffer with 4 channels (RGBA)

	GLCall(glGenTextures(1, &m_RendererID)); // Generate one texture ID
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID)); // Bind the texture

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // Sets out how the image will be sampled
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // 'Clamps' the texture to the edge of the image
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // 'Clamps' the texture to avoid tiling

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer)); // Uploads the texture data to the GPU
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer); // Frees the buffer of image data
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // Sets a texture slot to be active
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
