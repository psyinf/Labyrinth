#include "MazeGenerator.h"
#include "Helpers.h"
#include <algorithm>

MazeGenerator::MazeGenerator(uint16_t width, uint16_t height)
{
    mWidth = std::max<uint16_t>(width, 1u);
    mHeight = std::max<uint16_t>(height, 1u);
    Chamber c{0, mWidth - 1, 0, mHeight - 1};
    c.portals.insert({width / 2, 0});
    mChambers.push_back(c);
    
    generate(c, true);
}

Maze MazeGenerator::makeMaze(std::optional<std::reference_wrapper<MazePainter>> debug_painter)
{
    Maze     m(mWidth, mHeight);
    uint16_t chamber_no = 1;
    for (const auto& chamber : mChambers)
    {
        for (auto y = chamber.start_y; y <= chamber.end_y; ++y)
        {
            for (auto x = chamber.start_x; x <= chamber.end_x; ++x)
            {
                // draw only walls
                if (x == chamber.start_x || x == chamber.end_x || y == chamber.start_y || y == chamber.end_y)
                {
                    auto wt = WallType::WALL_HORIZONTAL;
                    if (chamber.portals.contains({x, y}))
                    {
                        wt = WallType::FREE;
                    }

                    m.set(x, y, wt);
                    if (debug_painter.has_value())
                    {
                        debug_painter.value().get().paint(x, y, wt);
                    }
                }
                else
                {
                    if (debug_painter.has_value())
                    {
                        debug_painter.value().get().paint(x, y, WallType::FREE);
                    }
                }
            }
            if (debug_painter.has_value())
            {
                debug_painter.value().get().paint(0, y, WallType::NEW_LINE);
            }
        }
        chamber_no++;
    }
    return m;
}

void MazeGenerator::generate(Chamber& c, bool hori_verti)
{
    // find a horizontal split
    if (hori_verti && c.getWidth() >= minWallLength)
    {
        auto split = rand_between_ex(c.start_x + 1, c.end_x - 1);
        // make chambers
        auto left = Chamber{c.start_x, split, c.start_y, c.end_y};
        auto right = Chamber{split, c.end_x, c.start_y, c.end_y};

        auto portal_pos = c.start_y + ((c.end_y - c.start_y) / 2);
        left.portals.insert(c.portals.cbegin(), c.portals.cend());
        right.portals.insert(c.portals.cbegin(), c.portals.cend());
        left.portals.insert({split, portal_pos});
        right.portals.insert({split, portal_pos});

        mChambers.push_back(left);
        mChambers.push_back(right);
        generate(left, !hori_verti);
        generate(right, !hori_verti);
    }
    else if (!hori_verti && c.getHeight() >= minWallLength)
    {
        auto split = rand_between_ex(c.start_y + 1, c.end_y - 1);
        // make chambers
        auto top = Chamber{c.start_x, c.end_x, c.start_y, split};
        auto bottom = Chamber{c.start_x, c.end_x, split, c.end_y};

        auto portal_pos = c.start_x + ((c.end_x - c.start_x) / 2);
        top.portals.insert(c.portals.cbegin(), c.portals.cend());
        bottom.portals.insert(c.portals.cbegin(), c.portals.cend());
        top.portals.insert({portal_pos, split});
        bottom.portals.insert({portal_pos, split});

        // #TODO find random portal(s)
        // recurse
        mChambers.push_back(top);
        mChambers.push_back(bottom);
        generate(top, !hori_verti);
        generate(bottom, !hori_verti);
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
