#include "Shader.h"

#include <fstream>
#include <sstream>

#include "glad/gl.h"

// Creates a shader program from filepath
ShaderProgram::ShaderProgram(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	m_ShaderSource = ParseShader(filepath);
	m_RendererID = CreateShader(m_ShaderSource.VertexSource, m_ShaderSource.FragmentSource); // Links the two shaders into one program and returns an id
}

ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void ShaderProgram::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void ShaderProgram::Unbind() const 
{

}

// Parses the shader file and separates the vertex and fragment shaders into separate code
struct ShaderProgramSource ShaderProgram::ParseShader(const std::string& filepath)
{
	ShaderProgramSource source;

	// Defines the type of shader we are currently parsing (useful for debugging)
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream file(filepath);
	std::string currentLine;

	if (!file.is_open())
	{
		LOG_ERR("Failed to open shader file: " << filepath);
		return source;
	}

	// Checks each line to determine if its a vertex or fragment shader, and appends the code to the appropriate string
	ShaderType currentShaderType = ShaderType::NONE;
	while (std::getline(file, currentLine))
	{
		if (currentLine.find("#shader") != std::string::npos)
		{
			if (currentLine.find("vertex") != std::string::npos)
			{
				currentShaderType = ShaderType::VERTEX;
			}
			else if (currentLine.find("fragment") != std::string::npos)
			{
				currentShaderType = ShaderType::FRAGMENT;
			}
		}
		else
		{
			switch (currentShaderType)
			{
				case ShaderType::VERTEX:
					source.VertexSource += currentLine + "\n";
					break;
				case ShaderType::FRAGMENT:
					source.FragmentSource += currentLine + "\n";
					break;
				case ShaderType::NONE:
					break;
			}
		}
	}

	file.close();
	return source;
}

unsigned int ShaderProgram::CompileShader(unsigned int type, const std::string& source)
{
	// Creates a vertex shader and returns an ID for it, converting it to a primitive data type for scalability with multiple graphics APIs
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	
	// Sets the source code for the shader
	GLCall(glShaderSource(id, 1, &src, nullptr)); 
	GLCall(glCompileShader(id));

	// Check for compile errors
	int status;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status)); // Gets the compile status of the shader
	if (status == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length)); // Gets the length of the error message
		char* message = new char[length]; // Allocates memory for the error message
		GLCall(glGetShaderInfoLog(id, length, &length, message)); // Gets the error message

		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(id)); // Deletes the shader if it failed to compile
		delete[] message; // Deletes the error message to prevent memory leaks

		return 0;
	}

	return id;
}

// Allows us to provide shaders to OpenGL as strings, link the two shaders as one program, and return an ID to be binded.
unsigned int ShaderProgram::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	// We would typically use GLuint here, but in order to scale with multiple graphics APIs, its best to use primitive data types

	// Creates the shader program as well as compiling the shaders
	unsigned int program = glCreateProgram(); 
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader); // Creates a vertex shader and returns an ID for it
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); // Creates a fragment shader and returns an ID for it

	// Attaches the shaders to the actual program
	GLCall(glAttachShader(program, vs)); 
	GLCall(glAttachShader(program, fs)); 

	// Links + validates the program (combines the shaders into one program)
	GLCall(glLinkProgram(program)); 
	GLCall(glValidateProgram(program));

	// Deletes the vertex + fragment shader (no longer needed after linking)
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs)); 

	return program; // Returns the ID of the program
}

// -----------------------------------------------------------------------
// UNIFORM SETTERS
// -----------------------------------------------------------------------

void ShaderProgram::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void ShaderProgram::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void ShaderProgram::SetUniform4f(const std::string& name, float values[])
{
	GLCall(glUniform4f(GetUniformLocation(name), values[0], values[1], values[2], values[3]));
}

void ShaderProgram::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	// Only passing one matrix, so the count is 1
	// The third parameter is false because glm::mat4 is column-major order, which is compatible with OpenGL's expectations
	// For the fourth parameter, we pass the address of the first element of the matrix to OpenGL (and the rest of the values are stored
	// sequentially in memory)
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, false, &matrix[0][0]));
}

GLint ShaderProgram::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name]; // If the uniform location is already cached, return it

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << '\n';

	m_UniformLocationCache[name] = location; // Cache the uniform location if it was found

	return location;
}
