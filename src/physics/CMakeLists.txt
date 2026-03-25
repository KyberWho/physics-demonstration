add_library(physics-engine STATIC
	"PhysicsEngine.h"
	"PhysicsEngine.cpp"
	"RigidBody.h" 
	"RigidBody.cpp"  
	"collision/CollisionHandler.cpp"
 "integrators/Euler.h")

target_include_directories(physics-engine PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory("shapes")

target_link_libraries(physics-engine 
	PUBLIC
		physics-shape
		utils
)