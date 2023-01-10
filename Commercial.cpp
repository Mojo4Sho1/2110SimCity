
#include "Commercial.h"

Commercial::Commercial()
{
    population = 0;
    xCoordinate = -1;
    yCoordinate = -1;
}

Commercial::Commercial(int x, int y)
{
    cellType = static_cast<Cell::Type>('C');
    population = 0;
    xCoordinate = x;
    yCoordinate = y;
}


void Commercial::IncreasePopulation()
{
    population+=1;
}