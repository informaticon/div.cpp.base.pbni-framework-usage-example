CMAKE_MINIMUM_REQUIRED(VERSION 3.0)


##################################################
#                 libFrameworkEx                 #
##################################################

project(div.cpp.miw.pbni-framework-example CXX)

add_library(libFrameworkEx SHARED
	"example.h"
	"example.cpp"
)

target_include_directories( libFrameworkEx PUBLIC
	"${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries( libFrameworkEx
	"${CMAKE_SOURCE_DIR}/lib/*.lib"
)

set_target_properties( libFrameworkEx PROPERTIES
	LINK_FLAGS "/MACHINE:X86"
	OUTPUT_NAME "lib.pbni.base.tse"
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

install(TARGETS libFrameworkEx
	RUNTIME DESTINATION ${A3_LIB_PATH}
)


set(PBNI_TARGET libFrameworkEx)
set(SUBFOLDER "lib.cpp.base.pbni-framework")
include("${SUBFOLDER}/lib.cpp.base.pbni-framework.cmake")