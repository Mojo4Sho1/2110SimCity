#ifndef COMMERICIALH
#define COMMERICIALH


#include "Good.h"


using namespace std;


class Commercial: public Cell {

    public:
        Commercial();
        Commercial(int x, int y);
        void IncreasePopulation();
};

#endif
