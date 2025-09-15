# Imports the precompiled GLFW library for Windows (Visual Studio 2022)
add_library(glfw STATIC IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES
	IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/glfw/lib/glfw3.lib"
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Finds + imports OpenGL (required by GLFW)
find_package(OpenGL REQUIRED)

# Creates an interface library to encapsulate third-party windowing dependencies
add_library(thirdparty_windowing INTERFACE)
target_link_libraries(thirdparty_windowing
	INTERFACE
		glfw
		OpenGL::GL
)