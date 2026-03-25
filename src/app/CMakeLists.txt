# Creates the actual executable for the physics simulation application
add_executable(physics-simulation "main.cpp")
set_target_properties(physics-simulation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copies resources folder to target directory after build
add_custom_target(copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/assets"
		"${CMAKE_BINARY_DIR}/assets"
		COMMENT "Copying assets to binary directory..."
)

add_dependencies(physics-simulation copy_resources)

target_link_libraries(physics-simulation
	PUBLIC
		core
		rendering
		thirdparty_rendering
		utils
)