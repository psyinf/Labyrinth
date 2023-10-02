#pragma once
#include <cstdint>
class Maze;
enum class WallType;

class MazePainter
{
public:
    virtual void paint(const Maze&) = 0;

    virtual void paint(uint16_t x, uint16_t, WallType) = 0;
};