cmake_minimum_required (VERSION 3.8)
set (APP_NAME Labyrinth)
set (CMAKE_CXX_STANDARD 20)

add_executable (${APP_NAME} 
	"Labyrinth.cpp" 
	"MazeGenerator.cpp" 
	"Helpers.h"
	"Maze.h"
	"MazePainter.h"
	"ConsoleMazePainter.h"
	"ConsoleMazePainter.cpp"
)

target_link_libraries(${APP_NAME} 
	PRIVATE 
)