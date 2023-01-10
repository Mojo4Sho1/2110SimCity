/*  
    Authors:        Joseph Caldwell (jcaldwell@my.unt.edu)
                    Libra Bates (libraBates@my.unt.edu)
                    Emma McKenzie
                    Aishat Oyedeji

    Date:           11/04/2022                   
    Instructor:     Curtis Chambers
    Description:    CSCE 2110: Project 1 - SimCity
     
*/


#include "City.h"


int main() {

City citySim;
int total = 0;
int total_after = 0;
int count = 0;
citySim.GetFileNameFromUser();
citySim.InitializeCity();
citySim.PopulateCellPopVec();
citySim.DisplayCity();

do
{
    citySim.CalcPopulation();
    total = citySim.GetTotalPopulation();
    citySim.UpdateCity();
    cout << endl;
    if(citySim.GetTimeStep() % citySim.GetRefreshRate() == 0) //only display states indicated by refreshrate
    {
        cout << "City State #" << citySim.GetTimeStep()<< ":";
        citySim.DisplayCity();
    }
    citySim.IncrementTimeStep();
    citySim.CalcPopulation();
    total_after = citySim.GetTotalPopulation();
    if(total == total_after)
    {
        break;
    }
}while(citySim.GetTimeStep() != citySim.GetMaxTime());
citySim.UpdatePollutionCity();
citySim.DisplayPollution();
cout << endl;
int first_x, first_y, second_x, second_y;
bool var = false;
cout << "Select a region to analyze further: " << endl;
do
{
    cout << "Enter the x coordinate of the first cell (from 0 to " << citySim.GetMax_X() - 1 << " ): "; cin >> first_x;
    cout << "Enter the y coordinate of the first cell (from 0 to " << citySim.GetMax_Y() - 1<< " ): "; cin >> first_y;
    cout << "Enter the x coordinate of the second cell (from 0 to " << citySim.GetMax_X() - 1 << " ): "; cin >> second_x;
    cout << "Enter the y coordinate of the second cell (from 0 to " << citySim.GetMax_Y() - 1 << " ): "; cin >> second_y;

    if(first_x < 0 || second_x < 0 || first_y <0 || second_y < 0 || first_x > citySim.GetMax_X() || first_y > citySim.GetMax_Y() || second_x > citySim.GetMax_X() || second_y > citySim.GetMax_Y() )
    {
        cout << "Error: Incorrect coordinates selected try again." << endl;
        var = true;
    }
}while(var);

citySim.DisplayCity(first_x, first_y, second_x, second_y);

    return 0;
}