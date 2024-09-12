cmake_minimum_required(VERSION 3.5)

project(div.cpp.base.pbni-framework-usage-example VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
	src/example.h
	src/example.cpp
)

set(PBNI_USE_STATIC_RUNTIME ON)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(pbni-framework CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC inf::pbni-framework)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${PBNI_FRAMEWORK_HEADERS})
