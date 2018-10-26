#pragma once
#include "Maze.h"
#include <vector>

class IGeneratorStrategy;

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
	using Chambers = std::vector<Chamber>;

	MazeGenerator() = default;

	Maze makeMaze(uint16_t width, uint16_t height,const IGeneratorStrategy& strategy);

	
private:
	std::unique_ptr<IGeneratorStrategy> mGeneratorStrategy;

	
};


