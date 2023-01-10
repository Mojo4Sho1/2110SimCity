
#include "Cell.h"

class Road : public Cell
{
        public:
            Road(int x, int y)  //constructor used to set the coordinates for a cell
            {
                cellType = static_cast<Cell::Type>('-');
                xCoordinate = x;
                yCoordinate = y;
            }
};