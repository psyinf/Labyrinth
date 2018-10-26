#include "MazeGenerator.h"
#include "Helpers.h"

#include <algorithm>
#include <numeric>
#include <random>

MazeGenerator::MazeGenerator(uint16_t width, uint16_t height, unsigned int seed)
	:mWidth(std::max<uint16_t>(width, 1u))
	,mHeight(std::max<uint16_t>(height, 1u))
{
	
	Chamber c{ 0, mWidth - 1 , 0, mHeight - 1 };
	
	if (0 == seed)
	{
		std::random_device rd;
		mSeed = rd();
	}
	generate(c);
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
					auto portal = chamber.hasPortalX(x) || chamber.hasPortalY(y);
					m.set(x, y, portal ? 0 : chamber_no);
				}
				
			}
		}
		chamber_no++;
	}
	return m;
}
//#TODO: pass the portals of the originating chamber to new ones to let them determine on their own
// that seems easier than checking for neighbors
void MazeGenerator::generate(Chamber& c)
{
	auto split_x = c.findSplitX();
	auto split_y = c.findSplitY();

	if (c.getWidth() >= 5)
	{
		auto portal_x = rand_between(c.start_x + 1, c.end_x - 1, mSeed);
		c.mPortalsX.push_back(portal_x); 
	}
	if (c.getHeight() >= 5)
	{
		auto portal_y = rand_between(c.start_y + 1, c.end_y - 1, mSeed);
		c.mPortalsY.push_back(portal_y);
	}
	if (split_x && split_y)
	{
		auto tl = Chamber{ c.start_x, split_x, c.start_y, split_y };
		auto tr = Chamber{ split_x, c.end_x, c.start_y, split_y };
		auto bl = Chamber{ c.start_x, split_x, split_y, c.end_y };
		auto br = Chamber{ split_x, c.end_x, split_y, c.end_y };
		tl.addPortals(c);
		tr.addPortals(c);
		bl.addPortals(c);
		br.addPortals(c);
		generate(tl);
		generate(tr);
		generate(bl);
		generate(br);
	}
	else if (!split_x && split_y)
	{
		auto top = Chamber{ c.start_x, c.end_x, split_y, c.end_y };
		auto bottom = Chamber{ c.start_x, c.end_x, split_y, c.end_y };
		top.addPortals(c);
		bottom.addPortals(c);
		generate(top);
		generate(bottom);
		mChambers.push_back(c);
	}
	else if (split_x && !split_y)
	{
		auto left = Chamber{ c.start_x, split_x, c.start_y, c.end_y };
		auto right = Chamber{ split_x, c.end_x, c.start_y, c.end_y };
		left.addPortals(c);
		right.addPortals(c);
		generate(left);
		generate(right);
		mChambers.push_back(c);
	}
	else if (!split_x && !split_y)
	{
		mChambers.push_back(c);
	}


	/*
	//find a horizontal split
	if (hori_verti && c.getWidth() >=5 )
	{
		auto split = rand_between(c.start_x + 2, c.end_x - 2, mSeed);
		//make chambers
		auto left = Chamber{ c.start_x, split, c.start_y, c.end_y };
		auto right = Chamber{ split, c.end_x, c.start_y, c.end_y };

		makePortals(left);
		makePortals(right);

		generate(left, !hori_verti);
		generate(right, !hori_verti);
	}
	else if(!hori_verti && c.getHeight() >= 5)
	{
		auto split = rand_between(c.start_y + 2, c.end_y - 2, mSeed);
		//make chambers
		auto top = Chamber{ c.start_x, c.end_x, c.start_y, split };
		auto bottom = Chamber{ c.start_x, c.end_x, split, c.end_y };

		makePortals(top);
		makePortals(bottom);

		generate(top, !hori_verti);
		generate(bottom, !hori_verti);
	}
	else
	{
		mChambers.push_back(c);
	}
	*/

	
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
	if (getWidth() > 5)
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
	if (getHeight() > 5)
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