# CMakeList.txt : CMake project for Labyrinth, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(unofficial-cairo CONFIG REQUIRED)

find_package(ZLIB REQUIRED)

# Add source to this project's executable.
set (APP_NAME Labyrinth)

add_executable (${APP_NAME} 
	"Labyrinth.cpp" "Labyrinth.h"
	"MazeGenerator.cpp" "MazeGenerator.h"
	"Helpers.h"
	"Maze.h"

)

target_link_libraries(${APP_NAME} 
	PRIVATE 
		unofficial::cairo::cairo 
		unofficial::cairo::cairo-gobject
		ZLIB::ZLIB
)

# TODO: Add tests and install targets if needed.
