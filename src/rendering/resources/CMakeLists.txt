add_library(resources
	"mesh/Mesh.h"
	"mesh/Mesh.cpp"
	"shaders/Shader.h"
	"shaders/Shader.cpp"
	"textures/Texture.h"
	"textures/Texture.cpp"
)

target_include_directories(resources PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	"${CMAKE_CURRENT_SOURCE_DIR}/mesh"
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders"
	"${CMAKE_CURRENT_SOURCE_DIR}/textures"
)

target_link_libraries(resources PUBLIC
	gpu
	thirdparty_rendering
	utils
)