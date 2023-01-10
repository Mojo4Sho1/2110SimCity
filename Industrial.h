#ifndef INDUSTRIALH
#define INDUSTRIALH


#include "Good.h"

#include <utility>

using namespace std;


class Industrial : public Cell {

    private:

        vector<Good *> goods;                           //vector of goods made
        vector<pair<Cell *, int> > pollutionPropList;

    public:
        Industrial();
        Industrial(int x, int y);
        int  GetPollutionPropListSize();
        void UpdateIndustrial();        //function will update population and make new goods and add them to vector

        void UpdatePollutionPropValues();                           //function increases pollution propagation values 
        void AddPairToPollutionPropList(pair<Cell *, int> Cell); 
        bool IsCellAvailable(int currX, int currY, int maxX, int maxY);     //checks if cell is availble to add to pollutionPropList      

        void UpdatePollution();         //function will update pollution values of Cell* in pollutionPropList. 
                                        //City class' UpdatePollutionCity() will call this function at the end of simulation
        void IncreasePopulation();
  
        int CountGoods();
        int CountAvailableGoods();

        Good* FindUnassignedGood();         
};

#endif
