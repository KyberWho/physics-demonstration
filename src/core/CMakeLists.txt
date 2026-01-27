# Sets up the core library
add_library(core STATIC
	"application/Application.cpp"
	"application/Application.h"
	"time/TimeManager.h" 
	"time/TimeManager.cpp"
	"input/Input.cpp" 
	"input/Input.h"
)

# Allows one singular point of configuration for the entire project
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Config.h
)
target_include_directories(core PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}					# Include source files in current directory (e.g src/core)
	${CMAKE_CURRENT_BINARY_DIR}					# Include generated config file (Config.h)
	
	"${CMAKE_CURRENT_SOURCE_DIR}/application"	
	"${CMAKE_CURRENT_SOURCE_DIR}/time"	
	"${CMAKE_CURRENT_SOURCE_DIR}/input"	
)

# Link any required libraries
target_link_libraries(core 
	PUBLIC
		thirdparty_rendering
		utils
)	