
#ifndef CITYH
#define CITYH

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "Cell.h"
#include "Commercial.h"
#include "Industrial.h"
#include "Residential.h"
#include "Worker.h"
#include "Good.h"
#include "Residential.h"
#include "Commercial.h"
#include "Industrial.h"
#include "PowerPlant.h"
#include "PowerLine.h"
#include "Combo.h"
#include "Road.h"

class City {

    private:
        int max_X = -1;                             //intialize calculated values                           
        int max_Y = -1;                             //
        int totalPopulation = 0;                    //
        int totalPollution = 0;                     //
        int totalWorkers = 0;                       //
        int totalGoods = 0;                         //
        int availableWorkers = 0;                   //
        int availableGoods = 0;                     //

        int refreshRate = 0;                        //values given from file
        int maxSteps = 0;                           //
        int timeStep = 0;                           //counter to track what time step simulation is on

        vector<Cell *> Cell_List;                   //vectors
        vector<Commercial *> commercial_List;       //
        vector<Industrial *> industrial_List;       //      Note: heriachy for updating cells-  Commercial->Industrial->Residential
        vector<Residential *> residential_List;     //
        vector<string> postProcessingVector;        //contains data from region file that has been processed, ie. adding commas and blank chars where needed


    public:
        void GetFileNameFromUser();                     //initializes simulation parameters given file config file from user
        void ReadInputFile(string fn);                  //config file input
        void ReadRegionFile(string fn);                 //region file input
        void SetMax_XandY();                            //sets max_X and max_Y
        int GetMax_X();
        int GetMax_Y();
        void PreProcessRegionData(ifstream& fileIn);    //adds blank chars where needed and ensures all values have a comma after them

        void InitializeCity();                      //creates vector of Cell*
        void InitializeAdjList();                   //
        void CalcPopulation();                      //iterates through each list of zones and counts population
        void CalcPollution();                       //iterates through all cells and counts pollution
        void CalcWorkers();                         //iterates through residential list and counts total workers
        void CalcGoods();                           //iterates through industrial list and counts total goods 
        void CalcFreeWorkers();                     //iterates through residential list and counts the amount of workers that are unemployed
        void CalcFreeGoods();                       //iterates through Industrial list and count the amount of good that aren't assigned to a store
        int GetTotalPopulation();
        int GetTotalPollution();
        int GetTotalWorkers();
        int GetTotalGoods();
        int GetTotalFreeGoods();
        int GetTotalFreeWorkers();
        int GetMaxTime();
        int GetTimeStep();
        int GetRefreshRate();
        Cell* GetCell(int x, int y);
        vector<Industrial *> GetIndustrialList();
        void UpdatePollutionCity();                              //called at very end of simulation to update all pollution values
        void UpdatePollutionPropList(Industrial * indusCell);    //needs to be called every time industrial zone's population is increased

        void DisplayCity();
        void DisplayCity(int,int,int,int); //Used for zooming in on grid to see specific zones                
        void DisplayPollution();                    //Used to display pollution values in cells instead of population values
        int DisplayResidentialPopulation(int index);
        int DisplayIndustrialPopulation(int index);
        int DisplayCommercialPopulation(int index);
        void UpdateWorkersAndGoods();               //Used to find available workers/goods within the city and then assign them to industrial/commercial cells that are ready to update
        void UpdateResidential();
        void UpdateIndustrial();
        void UpdateCommercial();
        void UpdateCity();                          //function to call most other functions to increase time step
        void PopulateCellPopVec();
        void UpdatePower();                         //should only be called once during simulation initilization
        void IncrementTimeStep();
};

#endif