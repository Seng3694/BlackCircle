cmake_minimum_required(VERSION 3.5)

project(BlackCircle)

add_subdirectory(ext)

set(INCLUDE_DIRS
	include
)

set(HEADERS
)

set(SOURCES
	src/Main.cpp
)

include_directories(${INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} imgui)
