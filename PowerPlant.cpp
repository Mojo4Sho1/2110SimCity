
#include "PowerPlant.h"

PowerPlant::PowerPlant()
{
    hasPower = true;
}

PowerPlant::PowerPlant(int x, int y)
{
    cellType = static_cast<Cell::Type>('P');
    hasPower = true;
    xCoordinate = x;
    yCoordinate = y;
}