#include "MazeGenerator.h"
#include "Helpers.h"

#include <algorithm>
#include <random>

MazeGenerator::MazeGenerator(uint16_t width, uint16_t height, unsigned int seed)
	:mWidth(std::max<uint16_t>(width, 1u))
	,mHeight(std::max<uint16_t>(height, 1u))
{
	
	Chamber c{ 0, mWidth - 1 , 0, mHeight - 1 };
	mChambers.push_back(c);
	if (0 == seed)
	{
		std::random_device rd;
		mSeed = rd();
	}
	generate(c, true);
}

Maze MazeGenerator::makeMaze()
{
	Maze m(mWidth, mHeight);
	uint16_t chamber_no = 1;
	for (const auto& chamber : mChambers)
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
					m.set(x, y, chamber_no);
				}
				
			}
		}
		chamber_no++;
	}
	return m;
}

void MazeGenerator::generate(Chamber& c, bool hori_verti)
{
	//find a horizontal split
	if (hori_verti && c.getWidth() >=5 )
	{
		auto split = rand_between(c.start_x + 2, c.end_x - 2, mSeed);
		//make chambers
		auto left = Chamber{ c.start_x, split, c.start_y, c.end_y };
		auto right = Chamber{ split, c.end_x, c.start_y, c.end_y };

		//#TODO find random portal(s)
		

		//mChambers.push_back(left);
		//mChambers.push_back(right);
		generate(left, !hori_verti);
		generate(right, !hori_verti);
	}
	else if(!hori_verti && c.getHeight() >= 5)
	{
		auto split = rand_between(c.start_y + 2, c.end_y - 2, mSeed);
		//make chambers
		auto top = Chamber{ c.start_x, c.end_x, c.start_y, split };
		auto bottom = Chamber{ c.start_x, c.end_x, split, c.end_y };

		//#TODO find random portal(s)
		//recurse
		//mChambers.push_back(top);
		//mChambers.push_back(bottom);
		generate(top, !hori_verti);
		generate(bottom, !hori_verti);
	}
	else
	{
		mChambers.push_back(c);
	}
	

	
}

uint16_t MazeGenerator::Chamber::getWidth()
{
	if (start_x > end_x)
	{
		throw std::logic_error("Invalid Chamber Width");
	}
	return end_x - start_x;
}

uint16_t MazeGenerator::Chamber::getHeight()
{
	if (start_y > end_y)
	{
		throw std::logic_error("Invalid Chamber Height");
	}
	return end_y - start_y;
}


