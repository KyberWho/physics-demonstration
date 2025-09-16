# Creates the actual executable for the physics simulation application
add_executable(physics-simulation "main.cpp")
set_target_properties(physics-simulation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(physics-simulation
	PUBLIC
		core
		thirdparty_rendering
		utils
)