# Finds + imports OpenGL (required by GLFW)
find_package(OpenGL REQUIRED)

# Fetches and builds the GLM library (header-only)
include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

# Adds all the subdirectories in the libs directory
add_subdirectory("glfw")
add_subdirectory("glad2")
add_subdirectory("stb_image")

# Creates an interface library to encapsulate third-party windowing dependencies
add_library(thirdparty_rendering INTERFACE)
target_link_libraries(thirdparty_rendering
	INTERFACE
		glfw
		glad
		glm::glm
		OpenGL::GL
		stb_image
)