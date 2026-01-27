#pragma once

#include <glad/gl.h>

#include "Logger.h"

// Encapsulates the shaders source code in one main data type (both vertex + fragment shaders)
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

// Encapsulates an entire OpenGL shader program
class ShaderProgram
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;

	struct ShaderProgramSource m_ShaderSource;
public:
	ShaderProgram(const std::string& filepath);
	~ShaderProgram();
	
	void Bind() const;
	void Unbind() const;
	
	struct ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	// Set uniforms (TO-DO for a later date)
	//void SetUniform1i(const std::string& name, int value);
	//void SetUniform1f(const std::string& name, float value);
	//void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};