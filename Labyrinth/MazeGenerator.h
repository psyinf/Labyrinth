#pragma once
#include "Maze.h"
#include <vector>



class MazeGenerator
{
public:

	struct Chamber
	{
		uint16_t getWidth() const;

		uint16_t getHeight() const;

		bool hasPortalX(uint16_t pos) const;

		bool hasPortalY(uint16_t pos) const;

		void addPortals(const Chamber& c);

		uint16_t findSplitX() const;
		uint16_t findSplitY() const;

		uint16_t start_x;
		uint16_t end_x;
		uint16_t start_y;
		uint16_t end_y;
		std::vector<uint16_t> mPortalsX;
		std::vector<uint16_t> mPortalsY;

	};


	MazeGenerator(uint16_t width, uint16_t height, unsigned int seed = 0);

	Maze makeMaze();

protected:
	void generate(Chamber& c);
	
private:
	std::vector<Chamber> mChambers;
	uint16_t mWidth	{ 0 };
	uint16_t mHeight{ 0 };
	unsigned int mSeed	{ 0 };
};


