#include "MazePainter.h"
class Maze;

class ConsoleMazePainter : public MazePainter
{
public:
    void paint(const Maze& m) override;

    void paint(uint16_t x, uint16_t, WallType) override;
};

class DebugMazePainter : public ConsoleMazePainter
{
public:
    void paint(uint16_t x, uint16_t, WallType) override;
};
