
#ifndef WORKERH
#define WORKERH

#include "Cell.h"

using namespace std;


class Worker {

    private:
        Cell * job = nullptr;

    public:
        Worker();                    //default constructor needs to set job equal to nullptr!
        void SetEmployment(Cell * job);
        Cell* IsEmployed();           //checks if worker is employed. May want to add function to display employment
};

#endif