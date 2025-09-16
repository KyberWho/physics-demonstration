# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.16)
project("physics-demonstration" VERSION 0.4)

# -------------------------------------------------------------------------------
# APPLICATION PARAMETERS (edit these values if needed)
# -------------------------------------------------------------------------------

set(OPENGL_DEBUG_MODE false)

# -------------------------------------------------------------------------------
# BUILD CONFIGURATION
# -------------------------------------------------------------------------------

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Include third-party dependencies
add_subdirectory("libs")

# Include engine modules.
add_subdirectory("src/app")
add_subdirectory("src/core")
add_subdirectory("src/utils")