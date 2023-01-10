#ifndef RESIDENTIALH
#define RESIDENTIALH


#include "Worker.h"

using namespace std;


class Residential : public Cell {

    private:
        vector<Worker *> workers;
    public:
        Residential();
        Residential(int x, int y);
        int CountWorkers();  
        int CountFreeWorkers();  
        Worker* FindFreeWorker();
        void IncreasePopulation();
              
 
};

#endif