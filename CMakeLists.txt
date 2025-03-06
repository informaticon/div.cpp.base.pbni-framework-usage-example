cmake_minimum_required(VERSION 3.15)

set(PBNI_SDK_DIRECTORY "C:/Program Files (x86)/Appeon/PowerBuilder 22.0/SDK/PBNI" CACHE PATH "Location of the required PBNI Sources")


project(div.cpp.base.pbni-framework-usage-example VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
	src/example.h
	src/example.cpp
)

find_package(lib.cpp.base.pbni-framework CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC lib.cpp.base.pbni-framework::lib.cpp.base.pbni-framework)

target_include_directories(${PROJECT_NAME} PUBLIC ${PBNI_SDK_DIRECTORY}/include)
target_precompile_headers(${PROJECT_NAME} PRIVATE "<PBNIFramework/pch.h>")
