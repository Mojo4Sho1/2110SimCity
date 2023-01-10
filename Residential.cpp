#include "Residential.h"

Residential::Residential(){  
    population = 0;
}

Residential::Residential(int x, int y)
{
    cellType = static_cast<Cell::Type>('R');
    xCoordinate = x;
    yCoordinate = y;
    population = 0;
}

int Residential::CountWorkers()
{
    vector<Worker*>::iterator iter;
    int workerCount = 0;
    for(iter = workers.begin(); iter != workers.end(); iter++)
    {
        workerCount++;
    }
    return workerCount;
}

int Residential::CountFreeWorkers()
{
    vector<Worker*>::iterator iter;
    int freeWorkerCount = 0;

    for(iter = workers.begin(); iter!=workers.end(); iter++)
    {
        if((*iter)->IsEmployed() == nullptr)
        {
            freeWorkerCount++;
        }
    }
    return freeWorkerCount;
}

Worker* Residential::FindFreeWorker()
{
    vector<Worker*>::iterator iter;
    for(iter = workers.begin(); iter != workers.end(); iter++)
    {
        if((*iter)->IsEmployed() == nullptr)
        {
            return (*iter);
        }
    }
        return nullptr;

}

void Residential::IncreasePopulation()
{
    population = population + 1;
    Worker* temp = new Worker;
    workers.push_back(temp);
}
