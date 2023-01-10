
#ifndef GOODH
#define GOODH

using namespace std;
class Commercial;
#include "Cell.h"
#include "Commercial.h"

class Good {

    private:
        Commercial* store;

    public:
        Good();                    //default constructor needs to set store equal to nullptr!
        void SetStore(Commercial* store);
        bool HasStore();           //checks if good has store / is availble to sell. May want to add function to display where sold
};

#endif