#pragma once
#include "Maze.h"
#include <set>
#include <optional>
#include "MazePainter.h"

class MazeGenerator
{
public:
    struct Chamber
    {
        uint16_t getWidth();

        uint16_t getHeight();

        uint16_t              start_x;
        uint16_t              end_x;
        uint16_t              start_y;
        uint16_t              end_y;
        std::set<std::pair<uint16_t, uint16_t>> portals;
    };

    MazeGenerator(uint16_t width, uint16_t height);

    Maze makeMaze(std::optional<std::reference_wrapper<MazePainter>> debug_painter);

protected:
    void                 generate(Chamber& c, bool horizontal_vertical);
    std::vector<Chamber> mChambers;
    uint16_t             mWidth{0};
    uint16_t             mHeight{0};
    const uint16_t       minWallLength{7};
};
