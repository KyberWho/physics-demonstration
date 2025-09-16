// This module handles logging functionality, including errors, warnings and info messages.
// TODO: Need to find a way to remove GLFW and avoid cyclic dependency
#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

// -------------------------------------------------------------------------------
// LOGGING MACROS
// -------------------------------------------------------------------------------

#define ASSERT(X) if (!(X)) __debugbreak(); // Breaks the program if the condition is false
#define GLCall(x) glClearError();\
    x;\
    ASSERT(glCheckError(#x, __FILE__, __LINE__))

#define LOG_INFO(msg)\
	std::cout << "[INFO] " << msg << std::endl;

#define LOG_ERR(err)\
	std::cerr << "[ERROR] " << err << std::endl;

#define LOG_WARN(warn)\
	std::cout << "[WARNING] " << warn << std::endl;

// -------------------------------------------------------------------------------
// LOGGING FUNCTIONS
// -------------------------------------------------------------------------------

// Clears any previous OpenGL errors
void glClearError();

// Outputs any OpenGL errors that have occurred
bool glCheckError(const char* function, const char* file, int line);