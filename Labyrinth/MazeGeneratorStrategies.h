#pragma once
#include "Helpers.h"

class IGeneratorStrategy
{
public:
	IGeneratorStrategy(unsigned int seed)
		:mSeed(seed)
	{}

	virtual MazeGenerator::Chambers generate(MazeGenerator::Chamber& start_chamber) const = 0;

protected:
	unsigned int mSeed;
};

class QuadGeneratorStrategy : public IGeneratorStrategy
{
public:
	QuadGeneratorStrategy(unsigned int seed)
		:IGeneratorStrategy(seed)
	{}

	virtual MazeGenerator::Chambers generate(MazeGenerator::Chamber& start_chamber) const
	{
		MazeGenerator::Chambers chambers;
		recursive_gen(start_chamber, chambers);

		return chambers;		
	}
protected:
	void recursive_gen(MazeGenerator::Chamber& c, MazeGenerator::Chambers& chambers) const
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
			auto tl = MazeGenerator::Chamber{ c.start_x, split_x, c.start_y, split_y };
			auto tr = MazeGenerator::Chamber{ split_x, c.end_x, c.start_y, split_y };
			auto bl = MazeGenerator::Chamber{ c.start_x, split_x, split_y, c.end_y };
			auto br = MazeGenerator::Chamber{ split_x, c.end_x, split_y, c.end_y };
			tl.addPortals(c);
			tr.addPortals(c);
			bl.addPortals(c);
			br.addPortals(c);
			recursive_gen(tl, chambers);
			recursive_gen(tr, chambers);
			recursive_gen(bl, chambers);
			recursive_gen(br, chambers);
		}
		else if (!split_x && split_y)
		{
			auto top = MazeGenerator::Chamber{ c.start_x, c.end_x, split_y, c.end_y };
			auto bottom = MazeGenerator::Chamber{ c.start_x, c.end_x, split_y, c.end_y };
			top.addPortals(c);
			bottom.addPortals(c);
			recursive_gen(top, chambers);
			recursive_gen(bottom, chambers);
			chambers.push_back(c);
		}
		else if (split_x && !split_y)
		{
			auto left = MazeGenerator::Chamber{ c.start_x, split_x, c.start_y, c.end_y };
			auto right = MazeGenerator::Chamber{ split_x, c.end_x, c.start_y, c.end_y };
			left.addPortals(c);
			right.addPortals(c);
			recursive_gen(left, chambers);
			recursive_gen(right, chambers);
			chambers.push_back(c);
		}
		else if (!split_x && !split_y)
		{
			chambers.push_back(c);
		}
	}
};

class LongestAxisStrategy : public IGeneratorStrategy
{
public:
	LongestAxisStrategy(unsigned int seed)
		:IGeneratorStrategy(seed)
	{}
public:
	virtual MazeGenerator::Chambers generate(MazeGenerator::Chamber& start_chamber) const override
	{
		MazeGenerator::Chambers chambers;
		split(start_chamber, chambers);
		return chambers;
	}
protected:
	void split(MazeGenerator::Chamber& c, MazeGenerator::Chambers& chambers) const
	{
		if (c.getWidth() > c.getHeight())
		{
			auto split_x = c.findSplitX();
			if (split_x > 0)
			{
				auto left	= MazeGenerator::Chamber{ c.start_x, split_x, c.start_y, c.end_y };
				auto right	= MazeGenerator::Chamber{ split_x, c.end_x, c.start_y, c.end_y };
				//#TODO: more checks required
				auto portal = rand_between(c.start_x + 1, split_x - 1, mSeed);
				left.addPortals(c);
				right.addPortals(c);
				left.mPortalsX.push_back(portal);
				right.mPortalsX.push_back(portal);
				
				split(left, chambers);
				split(right, chambers);
			}
			else
			{
				chambers.push_back(c);
			}
		}
		else
		{
			auto split_y = c.findSplitY();
			if (split_y > 0)
			{
				auto top	= MazeGenerator::Chamber{ c.start_x, c.end_x, c.start_y, split_y };
				auto bottom = MazeGenerator::Chamber{ c.start_x, c.end_x, split_y, c.end_y };

				auto portal = rand_between(c.start_y + 1, split_y - 1, mSeed);
				top.addPortals(c);
				bottom.addPortals(c);
				top.mPortalsY.push_back(portal);
				bottom.mPortalsY.push_back(portal);
				split(top, chambers);
				split(bottom, chambers);
			}
			else
			{
				chambers.push_back(c);
			}
		}
	}

};