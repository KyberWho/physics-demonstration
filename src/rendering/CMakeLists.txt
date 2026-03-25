# Sets up the rendering library
add_library(rendering STATIC
	"Renderer.h"
	"Renderer.cpp"
)

add_subdirectory("camera")
add_subdirectory("gpu")
add_subdirectory("resources")

target_include_directories(rendering PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rendering 
	PUBLIC
		camera
		gpu
		resources
		utils
)