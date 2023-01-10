#include <iostream>
using namespace std;
#include "Industrial.h"

Industrial::Industrial()
{
    population = 0;
    xCoordinate = -1;
    yCoordinate = -1;
}

Industrial::Industrial(int x, int y)
{
    cellType = static_cast<Cell::Type>('I');
    population = 0;
    xCoordinate = x;
    yCoordinate = y;
}
   
 

int Industrial::GetPollutionPropListSize() {

    return pollutionPropList.size();
}

void Industrial::UpdatePollutionPropValues() {              //increases all propagation values by 1

    for(int i = 0; i < pollutionPropList.size(); ++i) {

        pollutionPropList.at(i).second = pollutionPropList.at(i).second + 1;
    }
}
        

void Industrial::AddPairToPollutionPropList(pair<Cell *, int> Cell) {

    pollutionPropList.push_back(Cell);
}

bool Industrial::IsCellAvailable(int currX, int currY, int maxX, int maxY) {
    
    bool available = true;

    if(currX > maxX - 1) {              //out of range
        return false;
    }
    if(currY > maxY - 1) {              //out of range
        return false;
    }
    if(currX < 0 || currY < 0) {        //out of range
        return false;
    }
    for(int i = 0; i < pollutionPropList.size(); ++i) {         //already in pollutionPropList

        if(pollutionPropList.at(i).first->GetX_Cord() == currX && pollutionPropList.at(i).first->GetY_Cord() == currY) {
            return false;
        }
    }
    if(currX == xCoordinate && currY == yCoordinate) {          //dont want to add itself to its own pollution list
        return false;
    }

    return available;
}


void Industrial::UpdatePollution()
{
    for(int i = 0; i < pollutionPropList.size(); ++i) {

        Cell * tempCell = nullptr;
        int temp = 0;
        tempCell = pollutionPropList.at(i).first;
        temp = pollutionPropList.at(i).second;

        tempCell->IncreasePollution(temp);
    }
}

int Industrial::CountGoods()
{
    vector<Good *>::iterator iter;
    int goodCount = 0;
    for(iter = goods.begin(); iter!=goods.end(); iter++)
    {
        goodCount++;
    }

    return goodCount;
}

int Industrial::CountAvailableGoods()
{
    vector<Good *>::iterator iter;
    int availableGoodCount = 0;
    for(iter = goods.begin(); iter!=goods.end(); iter++)
    {
        if((!(*iter)->HasStore()))
        {
            availableGoodCount++;
        }
    }

    return availableGoodCount;
}     

Good* Industrial::FindUnassignedGood()
{
    vector<Good*>::iterator GoodIter;
    for(GoodIter = goods.begin(); GoodIter!= goods.end(); GoodIter++)
    {
        if(!((*GoodIter)->HasStore()))
        {
            return (*GoodIter);
        }
    }
        return nullptr;
    
}

void Industrial::IncreasePopulation() //increases the population of a industrial zone by one and adds a good object to goods vector
{
    population+=1;
    if(population > 1) {
        pollution+=1;
    }
    Good* temp = new Good();
    goods.push_back(temp);
}