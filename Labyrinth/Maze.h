#pragma once
#include <iostream>
#include <vector>
enum class WallType
{
    FREE,
    WALL_HORIZONTAL,
    WALL_VERTICAL,
    // TODO: CORNERS
	NEW_LINE,
};

class Maze
{
public: 

	//TODO: sparse matrix, skip list etc.
public:
	using value_type = WallType;
	Maze(uint16_t grid_size_x, uint16_t grid_size_y)
		: mGridSizeX(grid_size_x)
		, mGridSizeY(grid_size_y)
	{
		mFields.resize(mGridSizeX * mGridSizeY);
	}
			
	value_type get(uint16_t x, uint16_t y) const
	{
		return mFields[mGridSizeY * y + x];
	}
	void set(uint16_t x, uint16_t y, value_type value)
	{
		mFields[mGridSizeY * y + x] = value;
	}

	uint16_t getWidth() const { return mGridSizeX; }

	uint16_t getHeight() const { return mGridSizeY; }
private:
	uint16_t mGridSizeX{ 16 };
	uint16_t mGridSizeY{ 16 };
	std::vector<value_type> mFields;
};



