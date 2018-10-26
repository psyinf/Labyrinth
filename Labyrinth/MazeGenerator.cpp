#include "MazeGenerator.h"
#include "MazeGeneratorStrategies.h"
#include "Helpers.h"

#include <algorithm>
#include <numeric>
#include <random>


Maze MazeGenerator::makeMaze(uint16_t width, uint16_t height, const IGeneratorStrategy& strategy)
{
	

	Maze m(width, height);
	
	MazeGenerator::Chamber c{ 0,width-1, 0, height-1 };
	MazeGenerator::Chambers chambers;
	chambers = strategy.generate(c);
	
	uint16_t chamber_no = 1;
	for (const auto& chamber : chambers)
	{
		//draw only walls
		for (auto y = chamber.start_y; y <= chamber.end_y; ++y)
		{
			for (auto x = chamber.start_x; x <= chamber.end_x; ++x)
			{
				if (x == chamber.start_x 
					|| 
					x == chamber.end_x
					|| 
					y == chamber.start_y
					||
					y == chamber.end_y
					)
				{
					auto portal_x = chamber.hasPortalX(x);
					auto portal_y = chamber.hasPortalY(y);
					m.set(x, y, portal_x ? -1 : portal_y ? -2 : chamber_no);
				}
				
			}
		}
		chamber_no++;
	}
	return m;
}



uint16_t MazeGenerator::Chamber::getWidth() const
{
	if (start_x > end_x)
	{
		throw std::logic_error("Invalid Chamber Width");
	}
	return end_x - start_x;
}

uint16_t MazeGenerator::Chamber::getHeight() const
{
	if (start_y > end_y)
	{
		throw std::logic_error("Invalid Chamber Height");
	}
	return end_y - start_y;
}

bool MazeGenerator::Chamber::hasPortalX(uint16_t pos) const
{
	return std::count(std::begin(mPortalsX), std::end(mPortalsX), pos) > 0;
}


bool MazeGenerator::Chamber::hasPortalY(uint16_t pos) const
{
	return std::count(std::begin(mPortalsY), std::end(mPortalsY), pos) > 0;
}

void MazeGenerator::Chamber::addPortals(const Chamber& c)
{
	for (auto xportal : c.mPortalsX)
	{
		if (xportal > start_x && xportal < end_x)
		{
			mPortalsX.push_back(xportal);
		}
	}
	for (auto yportal : c.mPortalsY)
	{
		if (yportal > start_y && yportal < end_y)
		{
			mPortalsY.push_back(yportal);
		}
	}
}

uint16_t MazeGenerator::Chamber::findSplitX() const
{
	if (getWidth() > 6)
	{
		std::vector<uint16_t> valids(end_x - start_x - 4); //walls and directly adjacent are invalid
		std::iota(valids.begin(), valids.end(), start_x + 2);
		valids.erase(std::remove_if(valids.begin(), valids.end(), [this](const auto& valid) { return hasPortalX(valid) ;}), valids.end());
		if (!valids.empty())
		{
			std::random_shuffle(valids.begin(), valids.end());
			return valids.front();
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
uint16_t MazeGenerator::Chamber::findSplitY() const
{
	if (getHeight() > 6)
	{
		std::vector<uint16_t> valids(end_y - start_y - 4); //walls and directly adjacent are invalid
		std::iota(valids.begin(), valids.end(), start_y + 2);
		valids.erase(std::remove_if(valids.begin(), valids.end(), [this](const auto& valid) { return hasPortalY(valid); }), valids.end());
		if (!valids.empty())
		{
			std::random_shuffle(valids.begin(), valids.end());
			return valids.front();
		}
		else
		{
			return 0;
		}
	}
	return 0;
}