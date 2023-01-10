
#ifndef POWERLINEH
#define POWERLINEH

#include "Cell.h"
using namespace std;


class PowerLine : public Cell {

    public:
        PowerLine();               //default constructor needs to set hasPower = true           
        PowerLine(int x, int y);   //constructor used to set the coordinates for a cell
};

#endif