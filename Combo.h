
#ifndef COMBOH
#define COMBOH

#include "Cell.h"

using namespace std;


class Combo : public Cell {

    public:
        Combo();               //default constructor needs to set hasPower = true           
        Combo(int x, int y); //constructor used to set the coordinates for a cell
};

#endif