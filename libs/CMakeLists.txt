# Finds + imports OpenGL (required by GLFW)
find_package(OpenGL REQUIRED)

# Adds all the subdirectories in the libs directory
add_subdirectory("glfw")
add_subdirectory("glad2")

# Creates an interface library to encapsulate third-party windowing dependencies
add_library(thirdparty_rendering INTERFACE)
target_link_libraries(thirdparty_rendering
	INTERFACE
		glfw
		glad
		OpenGL::GL
)