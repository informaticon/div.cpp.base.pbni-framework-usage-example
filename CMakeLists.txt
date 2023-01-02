cmake_minimum_required(VERSION 3.0)


##################################################
#                    Options                     #
##################################################

set(OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out" CACHE PATH "Location of built dlls/libraries")
set(A3_LIB_PATH "C:/a3/erp.win.base.main/lib" CACHE PATH "Location of A3, is used to copy the resulting DLL")


##################################################
#                libUsageExample                 #
##################################################

project(div.cpp.base.pbni-framework-usage-example VERSION 1.0.0 LANGUAGES CXX)

add_library(libUsageExample SHARED
	src/example.h
	src/example.cpp
)

source_group("Source Files"
FILES
	src/example.h
	src/example.cpp
)

set_target_properties(libUsageExample
PROPERTIES 
	OUTPUT_NAME libUsageExample
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

install(TARGETS libUsageExample
	RUNTIME DESTINATION ${A3_LIB_PATH}
)


add_subdirectory(extern/lib.cpp.base.pbni-framework)
target_link_libraries(libUsageExample PRIVATE libPBNIFramework)
