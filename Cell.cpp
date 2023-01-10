#include "Cell.h"

Cell::Cell(){
    xCoordinate = -1;
    yCoordinate = -1;
    pollution = 0;
    hasPower = false;
}

Cell::Cell(int x, int y)
{
    cellType = static_cast<Cell::Type>(' ');
    xCoordinate = x;
    yCoordinate = y;
    pollution = 0;
    hasPower = false;
    population = 0;
    
}

void Cell::IncreasePollution(int val) {

    pollution = pollution + val;
}

Cell::Type Cell::GetType()
{
    return cellType;
}

int Cell::GetPollution()
{
    return pollution;
}

void Cell::AddCellToAdjList(Cell * cell) {

    adjacencyList.push_back(cell);
}

int Cell::GetX_Cord() {
    return xCoordinate;
}

int Cell::GetY_Cord() {
    return yCoordinate;
}


vector<Cell *> Cell::GetAdjList() {

    return adjacencyList;
}

int Cell::GetPop()
{
    return population;
}


bool Cell::CheckPower()
{
    vector<Cell*>::iterator iter;
    for(iter = adjacencyList.begin(); iter!= adjacencyList.end(); iter++)
    {
        if((*iter)->hasPower)
        {
            return true;
        }
    }

    return false;
}

void Cell::PopulateAdjacencyPopList()
{
    vector<Cell*>::iterator iter;
    for(iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++)
    {
        adjacencyPopList.push_back((*iter)->GetPop());
    }
}

void Cell::UpdatePopulationList()
{
    vector<Cell*>::iterator iter;
    int i = 0;
    for(iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++)
    {
        adjacencyPopList.at(i) = ((*iter)->GetPop());
        i++;
    }
}

bool Cell::CheckPopAdjListForPopulation(int num)
{   
    vector<int>::iterator iter;
    int count = 0;
    for(iter = adjacencyPopList.begin(); iter != adjacencyPopList.end(); iter++)
    {

        int pop = (*iter);
        if(num == 0)
        {
            if(pop == 1)
            {
                return true;
            }
        }
        else if(num == 1)
        {
            if(pop >= num)
            {
                count++;
                if(count == 2)
                {
                    return true;
                }
            }
        }
        else if(num == 2)
        {   
            if(pop >= 2)
                count++;
                if(count == 4)
                {
                    return true;
                }
        }
        else if(num == 3)
        {
            if(pop >= 3)
            {
                count++;
                if(count == 6)
                {
                    return true;
                }
            }
        }
        else if(num == 4)
        {
            if(pop >= 4)
            {
                count++;
                if(count == 8)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int Cell::GetTotalPopulationAdj()
{
    int sum = 0;
    vector<int>::iterator iter;
    for(iter = adjacencyPopList.begin(); iter != adjacencyPopList.end(); iter++)
    {
        sum+=*iter;
    }
    return sum;
}