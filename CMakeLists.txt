cmake_minimum_required(VERSION 3.0)

project(div.cpp.miw.pbni-framework-example)
set(PBNI_FRAMEWORK_EX_VERSION_MAJOR 0 CACHE STRING "Major Version of lib.cpp.base.pbni-framework")
set(PBNI_FRAMEWORK_EX_VERSION_MINOR 1 CACHE STRING "Minor Version of lib.cpp.base.pbni-framework")
set(PBNI_FRAMEWORK_EX_VERSION_BUGFIX 0 CACHE STRING "Bugfix Version of lib.cpp.base.pbni-framework")
set(PBNI_FRAMEWORK_EX_VERSION "${PBNI_FRAMEWORK_EX_VERSION_MAJOR}.${PBNI_FRAMEWORK_EX_VERSION_MINOR}.${PBNI_FRAMEWORK_EX_VERSION_BUGFIX}")

set(CMAKE_CXX_STANDARD 20)
# To be able to use __VA_OPT__
add_compile_options("/Zc:preprocessor")


##################################################
#                     Options                    #
##################################################


set(OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out" CACHE PATH "Location of built dlls/libraries")
set(A3_LIB_PATH "C:/Code/Cpp/erp.win.base.main/lib" CACHE PATH "Location of A3, is used to copy the resulting DLL")

set(PBNI_DIR "C:/Program Files (x86)/Appeon/PowerBuilder 17.0/SDK/PBNI" CACHE PATH "PATH of PowerBuilder Native Interface SDK")
set(PBNI_INCLUDE_DIR "${PBNI_DIR}/include" CACHE PATH "PowerBuilder Native Interface header files location")
set(PBNI_LIBRARY "${PBNI_DIR}/lib/pbni.lib" CACHE FILEPATH "PowerBuilder Native Interface library for release target")


##################################################
#                 libFrameworkEx                 #
##################################################

project("div.cpp.miw.pbni-framework-example" VERSION 1.0.0 LANGUAGES CXX)

add_library(libFrameworkEx SHARED
	"src/example.h"
	"src/example.cpp"
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


add_subdirectory("extern/lib.cpp.base.pbni-framework")
target_link_libraries(libFrameworkEx PRIVATE libFramework)
