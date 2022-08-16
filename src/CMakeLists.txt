CMAKE_MINIMUM_REQUIRED(VERSION 3.5)


##################################################
#                 libFrameworkEx                 #
##################################################

project("div.cpp.miw.pbni-framework-example" VERSION 1.0.0 LANGUAGES CXX)

add_library(libFrameworkEx SHARED
	"example.h"
	"example.cpp"
)

set_target_properties( libFrameworkEx PROPERTIES
	LINK_FLAGS "/MACHINE:X86"
	OUTPUT_NAME "libFrameworkEx"
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

install(TARGETS libFrameworkEx
	RUNTIME DESTINATION ${A3_LIB_PATH}
)


add_subdirectory(libFramework)
target_link_libraries(libFrameworkEx PRIVATE libFramework)
