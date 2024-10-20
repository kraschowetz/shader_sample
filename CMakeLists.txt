cmake_minimum_required(VERSION 3.5)
project(main)

option(VENDORED "use vendored libs" ON)

file(GLOB_RECURSE sources
	"${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_SOURCE_DIR}/src/*/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/*/*.hpp"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(VENDORED)
	add_subdirectory(lib/sdl EXCLUDE_FROM_ALL)
else()
	find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
	find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
	find_package(SDL2_image REQUIRED sdl2_image)
endif()

add_executable(main ${sources})

if(TARGET SDL2::SDL2main)
	target_link_libraries(main PRIVATE SDL2::SDL2main SDL2_image GL GLU GLEW)
endif()

add_compile_options(-02)

target_link_libraries(main PRIVATE SDL2::SDL2)
