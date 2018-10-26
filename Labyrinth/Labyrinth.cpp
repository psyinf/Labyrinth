// Labyrinth.cpp : Defines the entry point for the application.
//
#include "Labyrinth.h"
#include "MazeGenerator.h"
#include "MazeGeneratorStrategies.h"
#include <zlib.h>
#include <cairo/cairo.h>
#include <windows.h>


int main()
{
	MazeGenerator m;

	//QuadGeneratorStrategy qgs(99);
	LongestAxisStrategy qgs(99);
	auto maze = m.makeMaze(64, 64, qgs);

	ConsoleMazePainter cmp;
	cmp.paint(maze);
	for (auto i = 0; i < 64; ++i)
	{
		std::cout << "_";
	}
	std::cout << "Hello CMake." << std::endl;
	return 0;
}
