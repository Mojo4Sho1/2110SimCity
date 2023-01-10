
#include "Combo.h"

Combo::Combo()
{
    hasPower = true;
}

Combo::Combo(int x, int y)
{
    cellType = static_cast<Cell::Type>('#');
    xCoordinate = x;
    yCoordinate = y;
}