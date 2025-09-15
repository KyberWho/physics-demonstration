add_library(utils STATIC
	Miscellaneous.cpp
)

target_include_directories(core PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)