# Sets up the rendering library
add_library(rendering STATIC
	"mesh/VertexArray.h"
	"mesh/VertexArray.cpp"
	"mesh/VertexBuffer.h"
	"mesh/VertexBuffer.cpp"
	"mesh/VertexBufferLayout.h"
	"mesh/IndexBuffer.h" 
	"mesh/IndexBuffer.cpp"
	"shaders/Shader.h"
	"shaders/Shader.cpp" 
)

target_include_directories(rendering PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	"${CMAKE_CURRENT_SOURCE_DIR}/mesh"
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders"
)

target_link_libraries(rendering 
	PUBLIC
		thirdparty_rendering
		utils
)