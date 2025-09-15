# Sets up the core library
add_library(core STATIC
	Application.cpp
)

# Allows one singular point of configuration for the entire project
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Config.h
)
target_include_directories(core PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}					# Include source files in current directory (e.g src/core)
	${CMAKE_CURRENT_BINARY_DIR}					# Include generated config file (Config.h)
)

# Link any required libraries
target_link_libraries(core 
	PUBLIC
		thirdparty_windowing
		utils
)	