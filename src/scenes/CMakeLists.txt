add_library(scenes STATIC
	Scene.cpp
	Scene.h
	Entity.h
	Entity.cpp
)

target_include_directories(scenes PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(scenes
	PUBLIC
		rendering
		physics-engine
)