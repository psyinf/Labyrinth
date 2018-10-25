// Labyrinth.cpp : Defines the entry point for the application.
//
#include "Labyrinth.h"
#include "MazeGenerator.h"
#include <zlib.h>
#include <cairo/cairo.h>
#include <windows.h>


int main()
{
	MazeGenerator m(64,64);
	//test simple cairo
	auto maze = m.makeMaze();

	ConsoleMazePainter cmp;
	cmp.paint(maze);
	for (auto i = 0; i < 64; ++i)
	{
		std::cout << "_";
	}
	std::cout << "Hello CMake." << std::endl;
	return 0;
}
