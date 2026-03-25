#pragma once

// TODO: REFACTOR THIS TO WORK WITH TEXTURES UNDER MATERIALS FOR BETTER ORGANIZATION (TO DO IN FUTURE ITERATIONS)

#include <string>
#include <unordered_map>

#include "glad/gl.h"
#include "glm/glm.hpp"

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

		mutable std::unordered_map<std::string, GLint> m_UniformLocationCache; // Cache for uniform locations to avoid redundant calls to glGetUniformLocation
	public:
		ShaderProgram(const std::string& filepath);
		~ShaderProgram();
	
		void Bind() const;
		void Unbind() const;
	
		struct ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		// Sets uniforms
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float values[]);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

		GLint GetUniformLocation(const std::string& name) const;
};