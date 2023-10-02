
#include "ConsoleMazePainter.h"
#include "MazeGenerator.h"
#include <windows.h>

int main()
{
    const auto    dimension = 64u;
    MazeGenerator m(dimension, dimension/2);
    auto          debug_painter = DebugMazePainter{};
    auto          maze = m.makeMaze(std::reference_wrapper(debug_painter));

    ConsoleMazePainter cmp;
    cmp.paint(maze);

    return 0;
}
