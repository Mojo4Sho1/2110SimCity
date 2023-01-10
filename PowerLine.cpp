#include "PowerLine.h"

PowerLine::PowerLine()
{
    hasPower = true;
}

PowerLine::PowerLine(int x, int y)
{
    cellType = static_cast<Cell::Type>('T');
    hasPower = true;
    xCoordinate = x;
    yCoordinate = y;
}