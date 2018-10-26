#pragma once
#include <iostream>
#include <vector>

class Maze
{
	
public:
	using value_type = int;
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


class IMazePainter
{
public:
	virtual void paint(const Maze&) = 0;
};



class ConsoleMazePainter : public IMazePainter
{

public:
	virtual void paint(const Maze& m) override
	{
		std::cout << "\n";
		for (auto y = 0; y < m.getHeight(); ++y)
		{
			for (auto x = 0; x < m.getWidth(); ++x)
			{
				//std::cout << (m.get(x, y) ? "*" : " ");
				//std::cout << m.get(x, y);
				auto v = m.get(x, y);
				if (v > 0)
				{
					std::cout << char(178);
				}
				if (v == -1)
				{
					std::cout << "_";
				}
				if (v == -2)
				{
					std::cout << "x";
				}
				if (v == 0)
				{
					std::cout << " ";
				}
			}
			std::cout << "\n";
		}
	}
};

