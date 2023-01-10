
#ifndef POWERPLANTH
#define POWERPLANTH

#include "Cell.h"

using namespace std;


class PowerPlant : public Cell {

    public:
        PowerPlant();               //default constructor needs to set hasPower = true           
        PowerPlant(int x, int y);   //constructor used to set the coordinates for a cell
};

#endif