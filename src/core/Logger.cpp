#include "Logger.h"

void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glCheckError(const char* function, const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
			case GL_INVALID_ENUM:                  error = "GL_INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "GL_INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "GL_INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:                error = "GL_STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW:               error = "GL_STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY:                 error = "GL_OUT_OF_MEMORY"; break;
		}
		LOG_ERR("(OPENGL) " << error << " at " << function << " in " << file << " (" << line << ")");
		
		return false;
	}

	return true;
}