
#ifndef CELLH
#define CELLH

#include <iostream>
#include <vector>

using namespace std;


class Cell {

    public:
        Cell();
        Cell(int x, int y);  //constructor used to set the coordinates for a cell
        enum Type {
                   Residential = 'R',
                   Industrial  = 'I',
                   Commercial  = 'C',
                   PowerP      = 'P',       //power plant
                   PowerL      = 'T',       //power line
                   Road        = '-',
                   Combo       = '#',       //power plant & power line
                   Blank       = ' ',       //empty space
        };                           //default constructor needs to initialize hasPower variable to false!
        bool CheckPower();
        void IncreasePollution(int val);
        void AddCellToAdjList(Cell * cell);
        int  GetPollution();                //returns pollution value
        int  GetX_Cord();                   //returns xCoordinate
        int  GetY_Cord();                   //returns yCoordinate
        Type GetType();
        vector<Cell *> GetAdjList();        //returns adjacency list vector
        int GetPop();
        void PopulateAdjacencyPopList(); //populates adjacencyPopList with the population values of the adjacent cells prior to being updated
        void UpdatePopulationList(); //after all cells have had their populations updated, adjacencyPopList is updated to reflect new values
        bool CheckPopAdjListForPopulation(int num); //population of current cell is passed and then requirements for population growth are checked
        int GetTotalPopulationAdj(); //returns a integer value that reflects the total amount of population in a cell's adjacency list

    protected:
        int xCoordinate = -1;
        int yCoordinate = -1;
        int pollution = 0;
        Type cellType;
        bool hasPower;
        int population = 0;
        vector<Cell *> adjacencyList;
        vector<int> adjacencyPopList;
};

#endif