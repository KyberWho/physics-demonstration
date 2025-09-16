add_library(glad STATIC
	"src/gl.c"
)

#"include/glad/gl.h"
#"include/KHR/khrplatform.h"

target_include_directories(glad PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# glad_add_library(glad_gl_core_mx_33 REPRODUCIBLE MX API gl:core=3.3)