# Holds all the buffer classes (isolated from the rest of the rendering system)
# so that they can be used by other modules (e.g., the mesh module).
add_library(gpu STATIC
	"Buffer.h" 
	"Buffer.cpp"
	"VertexBufferLayout.h"
)

target_include_directories(gpu PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gpu
	PRIVATE
		thirdparty_rendering
		utils
)