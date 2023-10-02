#include "ConsoleMazePainter.h"
#include "Maze.h"
#include <thread>
#ifdef _WINDOWS
#include <windows.h>
void setConsolePosition(std::uint16_t x, std::uint16_t y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}
#endif
void ConsoleMazePainter::paint(const Maze& m)
{
    std::cout << "\n";
    for (auto y = 0; y < m.getHeight(); ++y)
    {
        for (auto x = 0; x < m.getWidth(); ++x)
        {
            paint(x, y, m.get(x, y));
        }
        paint(0, y, WallType::NEW_LINE);
    }
}

void ConsoleMazePainter::paint(uint16_t x, uint16_t y, WallType wt)
{
    setConsolePosition(x, y);
    switch (wt)
    {
    case WallType::FREE:
        std::cout << " ";
        break;
    case WallType::WALL_HORIZONTAL:
        [[fallthrough]];
    case WallType::WALL_VERTICAL:
        std::cout << "*";
        break;

    default:
        break;
    case WallType::NEW_LINE:
        std::cout << "\n";
        break;
    }
}

void DebugMazePainter::paint(uint16_t x, uint16_t y, WallType wt)
{
    ConsoleMazePainter::paint(x, y, wt);
    if (wt != WallType::FREE)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}
