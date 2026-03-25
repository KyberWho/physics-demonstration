add_library(physics-shape STATIC
	"Box.h"
	"Box.cpp"
 "Shape.h")

target_include_directories(physics-shape PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(physics-shape PUBLIC
	utils
)