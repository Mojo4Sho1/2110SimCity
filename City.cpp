
#include "City.h"


void City::GetFileNameFromUser() {

    string config_FileName;  

    cout << endl;
    cout << "Welcome to SimCity." << endl;
    cout << "Please provide the configuration file name: ";
    cin >> config_FileName;                                 //read filename from user
    cout << endl;

    ReadInputFile(config_FileName);                         //call function  
}

void City::ReadInputFile(string fn) {

    ifstream configStream;
    string region_FileName;

    string sub; 
    int index; 

    configStream.open(fn.c_str());                          //open config file

    if(configStream.fail()) {
        cout << "File Error. Config" << endl;
        exit(1);
    }
                                                                  
    
    getline(configStream, sub);                                     //first line is region file name
    index = sub.find(":");
    region_FileName = sub.substr(index + 1);

    getline(configStream, sub);                                     //second line is max steps for simulation
    index = sub.find(":");
    maxSteps = stoi(sub.substr(index + 1));

    getline(configStream, sub);                                     //third line is refresh rate for simulation
    index = sub.find(":");
    refreshRate = stoi(sub.substr(index + 1));

    configStream.close();                                           //close config file


    ReadRegionFile(region_FileName);                         //call function
}

void City::ReadRegionFile(string fn) {

    string line;

    ifstream regionStream;

    regionStream.open(fn.c_str());                           //open region file  

    if(regionStream.fail()) {                                //open region file
        cout << "File Error. Region" << endl;
        exit(1);
    }

    PreProcessRegionData(regionStream);        
    
    regionStream.close();                                    //close region file

    SetMax_XandY(); 
}

void City::SetMax_XandY() {     

    char comma = ',';
    int currX = 0;

    max_X = currX;
    max_Y = postProcessingVector.size();

    for(int i = 0; i < postProcessingVector.size(); ++i) {

        for(int j = 0; j < postProcessingVector.at(i).size(); ++j) {

            if(postProcessingVector.at(i).at(j) == comma) {
                currX = currX + 1;
            }
        }
        if(currX > max_X) {
                max_X = currX;
            }
        currX = 0;
    }
}

void City::PreProcessRegionData(ifstream& fileIn) {  //function adds blank chars where needed and ensures all values have a comma after them

    string line;
    string blank = " ";
    char comma = ',';

    vector<int> indexList;      //used for inserting blanks
    int count = 1;              //counter for preprocessing


    while(fileIn.peek() != EOF) {

        getline(fileIn, line);

        postProcessingVector.push_back(line);       //call push_back to add string to the end of vector

    }


    for(int i = 0; i < postProcessingVector.size(); ++i) {

        if(postProcessingVector.at(i).back() != comma) {
            postProcessingVector.at(i).push_back(comma);
        }
        if(postProcessingVector.at(i).front() == comma) {
            postProcessingVector.at(i).insert(0, blank);
        }

        for(int j = 0; j < postProcessingVector.at(i).size() - 1; ++j) {

            if((postProcessingVector.at(i).at(j) == comma) && (postProcessingVector.at(i).at(j + 1) == comma) ) {

                    indexList.push_back(j + count);
                    count = count + 1;
            }
        }


        for(int k = 0; k < indexList.size(); ++k) {

            postProcessingVector.at(i).insert(indexList.at(k), blank);
        }

        indexList.clear();
        count = 1;        
    }

}

Cell* City::GetCell(int x, int y) {

    int index = -1;
    Cell * tempCell = nullptr;

    if(y == 0) {
        index = x;
    }

    else {
        index = y * max_X + x;
    }

    tempCell = Cell_List.at(index);

    return tempCell;
}

void City::InitializeCity() {

    Cell::Type ch;
    int y = 0;      //y = i
    int x = 0;      //x needs to increase after every constructor call and reset to 0 when j increases
    Cell* temp;
    Residential* res;
    Industrial* ind;
    Commercial* com;

    for(int i = 0; i < postProcessingVector.size(); ++i) {

        x = 0;
        y = i;

        for(int j = 0; j < postProcessingVector.at(i).size(); ++j) {
            ch = static_cast<Cell::Type>(postProcessingVector.at(i).at(j));

            switch(ch)
            {
                case Cell::Residential:
                    res = new Residential(x, y);
                    temp = res;
                    Cell_List.push_back(temp);
                    residential_List.push_back(res);
                    x = x + 1;
                    break;

                case Cell::Industrial:
                    ind = new Industrial(x, y);
                    temp = ind;
                    Cell_List.push_back(temp);
                    industrial_List.push_back(ind);
                    x = x + 1;
                    break;
                
                case Cell::Commercial:
                    com = new Commercial(x, y);
                    temp = com;
                    Cell_List.push_back(temp);
                    commercial_List.push_back(com);
                    x = x + 1;
                    break;

                case Cell::PowerP:
                    temp = new PowerPlant(x, y);
                    Cell_List.push_back(temp);
                    x = x + 1;
                    break;

                case Cell::PowerL:
                    temp = new PowerLine(x, y);
                    Cell_List.push_back(temp);
                    x = x + 1;
                    break;

                case Cell::Road:
                    temp = new Road(x, y);
                    Cell_List.push_back(temp);
                    x = x + 1;
                    break;

                case Cell::Combo:
                    temp = new Combo(x, y);
                    Cell_List.push_back(temp);
                    x = x + 1;
                    break;

                case Cell::Blank:
                    temp = new Cell(x, y);
                    Cell_List.push_back(temp);
                    x = x + 1;
                    break;
                default:
                continue;
                break;
            }

        }
    }
    InitializeAdjList();
}


void City::InitializeAdjList() {    //adajacency list consists of 4 corner cases, 4 edge cases, and all other cases

    Cell * tempCell;
    int currX = -1;
    int currY = -1;


    for(int i = 0; i < Cell_List.size(); ++i) {     //Corner cases -> Edge cases -> All other cases


        if(Cell_List.at(i)->GetX_Cord() == 0 && Cell_List.at(i)->GetY_Cord() == 0) {            //corner case #1    TOP LEFT


            tempCell = GetCell(1,0);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(1,1);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(0,1);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
        }

       

        else if((Cell_List.at(i)->GetX_Cord() == max_X - 1) && (Cell_List.at(i)->GetY_Cord() == 0)) {        //corner case #2    TOP RIGHT

            tempCell = GetCell(max_X - 2, 0);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(max_X - 2, 1);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(max_X - 1, 1);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
        } 

        

        else if((Cell_List.at(i)->GetX_Cord() == 0) && (Cell_List.at(i)->GetY_Cord() == max_Y - 1)) {        //corner case #3    BOTTOM LEFT

            tempCell = GetCell(0, max_Y - 2);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(1, max_Y - 2);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(1, max_Y - 1);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
        }


        else if((Cell_List.at(i)->GetX_Cord() == max_X - 1) && (Cell_List.at(i)->GetY_Cord() == max_Y - 1)) {    //corner case #4    BOTTOM RIGHT

            tempCell = GetCell(max_X - 1, max_Y - 2);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(max_X - 2, max_Y - 2);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
            tempCell = GetCell(max_X - 2, max_Y - 1);
            Cell_List.at(i)->AddCellToAdjList(tempCell);
        }

        else{           //*EDGE CASES*//

            if(Cell_List.at(i)->GetX_Cord() == 0) {                                 //edge case #1      LEFT SIDE
                    
                currY = Cell_List.at(i)->GetY_Cord();

                tempCell = GetCell(0, currY - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(1, currY - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(1, currY);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(0, currY + 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(1, currY + 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
            }
        
            else if(Cell_List.at(i)->GetY_Cord() == 0) {                             //edge case #2      TOP SIDE 

                currX = Cell_List.at(i)->GetX_Cord();

                tempCell = GetCell(currX - 1, 0);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX - 1, 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX, 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX + 1, 0);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX + 1, 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
            }

            else if(Cell_List.at(i)->GetX_Cord() == max_X - 1) {                      //edge case #3      RIGHT SIDE

                currY = Cell_List.at(i)->GetY_Cord();

                tempCell = GetCell(max_X - 1, currY - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(max_X - 2, currY - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(max_X - 2, currY);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(max_X - 2, currY + 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(max_X - 1, currY + 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
            }

            else if(Cell_List.at(i)->GetY_Cord() == max_Y - 1) {                       //edge case #4   BOTTOM SIDE

                currX = Cell_List.at(i)->GetX_Cord();

                tempCell = GetCell(currX - 1, max_Y - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX - 1, max_Y - 2);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX, max_Y - 2);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX + 1, max_Y - 2);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX + 1, max_Y - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
            }

            else {      //ALL OTHER CASES BESIDES CORNERS AND EDGES

                currX = Cell_List.at(i)->GetX_Cord();
                currY = Cell_List.at(i)->GetY_Cord();

                tempCell = GetCell(currX - 1, currY - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX, currY - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX + 1, currY - 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX - 1, currY);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX + 1, currY);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX - 1, currY + 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX, currY + 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
                tempCell = GetCell(currX + 1, currY + 1);
                Cell_List.at(i)->AddCellToAdjList(tempCell);
            }
        }
    }


//following code initializes industrial_list's industrial pointers' pollutionPropLists

    if(!industrial_List.empty()) {

        Cell * copyCell = nullptr;
        int copyX;
        int copyY;
        Cell * tempCell = nullptr;
        vector<Cell *> tempAdjList;
        pair<Cell *, int> tempPair;



        for(int i = 0; i < industrial_List.size(); ++i) {

            //cout << "This works." << endl;

            copyX = industrial_List.at(i)->GetX_Cord();
            copyY = industrial_List.at(i)->GetY_Cord();
            copyCell = GetCell(copyX, copyY);

            tempAdjList = copyCell->GetAdjList();

            //cout << "Adjacency List size is: " << tempAdjList.size() << endl;

            for(int j = 0; j < tempAdjList.size(); ++j) {

                tempCell = tempAdjList.at(j);
                tempPair.first = tempCell;
                tempPair.second = 0;
                industrial_List.at(i)->AddPairToPollutionPropList(tempPair);
            }
        }
    }



}


vector<Industrial *> City::GetIndustrialList() {

    return industrial_List;
}


void City::UpdatePollutionCity() {

    for(int i = 0; i < industrial_List.size(); ++i) {

        industrial_List.at(i)->UpdatePollution();
    }
}


void City::UpdatePollutionPropList(Industrial * indusCell) {

    int population = indusCell->GetPop();

    pair<Cell *, int> tempPair;
    Cell * tempCell = nullptr;

    if(population <= 2) {

        if(population == 1 || population == 0) {       //do nothing
            return;
        }
        if(population == 2) {       //set each pollution value to all adjacent cells to 1

            indusCell->UpdatePollutionPropValues();
        }
    }

    else {

        int xCoord = indusCell->GetX_Cord();
        int yCoord = indusCell->GetY_Cord();
        int tempX = -1;
        int tempY = -1;

        for(int x = 0; x < population; ++x) {            //nested loop to find new cells by extending search radius outwards

            for(int y = 0; y < population; ++y) {

                tempX = xCoord - x;
                tempY = yCoord - y;
                if(indusCell->IsCellAvailable(tempX, tempY, max_X, max_Y)) {        //if cell exists in matrix and is available
                    tempCell = GetCell(tempX, tempY);
                    tempPair.first = tempCell;
                    tempPair.second = 0;
                    indusCell->AddPairToPollutionPropList(tempPair);                //add to pollutionPropList
                }
                tempX = xCoord + x;
                tempY = yCoord + y;
                if(indusCell->IsCellAvailable(tempX, tempY, max_X, max_Y)) {        //if cell exists in matrix and is available
                    tempCell = GetCell(tempX, tempY);
                    tempPair.first = tempCell;
                    tempPair.second = 0;
                    indusCell->AddPairToPollutionPropList(tempPair);                //add to pollutionPropList
                }

               
                tempX = xCoord + x;
                tempY = yCoord - y;
                if(indusCell->IsCellAvailable(tempX, tempY, max_X, max_Y)) {        //if cell exists in matrix and is available
                    tempCell = GetCell(tempX, tempY);
                    tempPair.first = tempCell;
                    tempPair.second = 0;
                    indusCell->AddPairToPollutionPropList(tempPair);                //add to pollutionPropList
                }
                tempX = xCoord - x;
                tempY = yCoord + y;
                if(indusCell->IsCellAvailable(tempX, tempY, max_X, max_Y)) {        //if cell exists in matrix and is available
                    tempCell = GetCell(tempX, tempY);
                    tempPair.first = tempCell;
                    tempPair.second = 0;
                    indusCell->AddPairToPollutionPropList(tempPair);                //add to pollutionPropList
                }

            }
        }

        indusCell->UpdatePollutionPropValues();     //adds one to all propagation values in list
    }


}


void City::DisplayCity()
{
    vector<Cell *>::iterator iter;
    int count = 0, count2 = 0;
    int  resIndex = 0, comIndex = 0, indIndex = 0;
    cout << endl;
    cout << "Our City Display:" << endl;
    cout << "| ";
    for(iter = Cell_List.begin(); iter != Cell_List.end(); iter++)
    {   
        Cell::Type control = (*iter)->GetType();
        count++;
        switch(control) //used to identify what kind of cell is being accessed and print the correct character
        {

            case Cell::Residential:
            {
                if(DisplayResidentialPopulation(resIndex) != 0)
                {
                    cout << DisplayResidentialPopulation(resIndex) << " | ";
                }
                else
                {
                    cout << 'R' << " | ";
                }
                resIndex++;
                break;
            }
            case Cell::Industrial:
            {
                if(DisplayIndustrialPopulation(indIndex) != 0)
                {
                    cout << DisplayIndustrialPopulation(indIndex) << " | ";
                }
                else
                {
                    cout << 'I' << " | ";
                }
                indIndex++;
                break;
            }
            case Cell::Commercial:
            {
                if(DisplayCommercialPopulation(comIndex) != 0)
                {
                    cout << DisplayCommercialPopulation(comIndex) << " | ";
                }
                else
                {
                    cout << 'C' << " | ";
                }
                comIndex++;
                break;
            }
            case Cell::PowerL:
            {
                cout << 'T' << " | ";
                break;
            }
            case Cell::PowerP:
            {   
                cout << 'P' << " | ";
                break;
            }
            case Cell::Combo:
            {
                cout << '#' << " | ";
                break;
            }
            case Cell::Road:
            {
                cout << '-' << " | ";
                break;
            }
            case Cell::Blank:
            {
                cout << ' ' << " | ";
                break;
            }
            
        }
        if( count == max_X && count2 != max_Y - 1) //formatting
        {
            count2++;
            cout << endl;
            cout << "| ";
            count = 0;
        }
    }
    cout << endl;

    cout << "Current Available Workers: " << availableWorkers << endl;
    cout << "Current Available Goods: " << availableGoods << endl;
}

int City::DisplayResidentialPopulation(int index)
{
    return residential_List.at(index)->GetPop();
}

int City::DisplayIndustrialPopulation(int index)
{
    return industrial_List.at(index)->GetPop();
}

int City::DisplayCommercialPopulation(int index)
{
    return commercial_List.at(index)->GetPop();
}
void City::UpdateCommercial() 
{
    vector<Industrial*>::iterator IndIter;
    vector<Commercial*>::iterator ComIter;
    vector<Residential*>::iterator ResIter;
    Good* freeGood;
    Worker* freeWorker;

    for(ComIter = commercial_List.begin(); ComIter != commercial_List.end(); ComIter++)
    {
        for(ResIter = residential_List.begin(); ResIter != residential_List.end(); ResIter++) //Finds an available worker
        {
            if((*ResIter)->FindFreeWorker() != nullptr)
            {
                freeWorker = (*ResIter)->FindFreeWorker();
                break;
            }

        }


        for(IndIter = industrial_List.begin(); IndIter != industrial_List.end(); IndIter++)//Finds an available good
        {
            if((*IndIter)->FindUnassignedGood() != nullptr)
            {
                freeGood = (*IndIter)->FindUnassignedGood();
                break;
            }
        }
                if(availableWorkers > 0 && availableGoods > 0)
            {
                if(((*ComIter)->GetTotalPopulationAdj() == 0) && ((*ComIter)->GetPop() == 0)) //if there are no populated cells around this cell and it has a population of 0 and has power its population will increase
                {
                    if((*ComIter)->CheckPower())
                    {
                        (*ComIter)->IncreasePopulation();
                        freeWorker->SetEmployment((*ComIter));
                        freeGood->SetStore((*ComIter));
                        availableGoods-=1;
                        availableWorkers-=1;
                    }
                }
                else if((*ComIter)->GetPop() == 0)
                {
                    if((*ComIter)->CheckPopAdjListForPopulation(0))
                        {
                        
                            (*ComIter)->IncreasePopulation();
                            freeWorker->SetEmployment((*ComIter));
                            freeGood->SetStore((*ComIter));
                            availableGoods-=1;
                            availableWorkers-=1;
                        }
                }
                else if((*ComIter)->GetPop() == 1)
                {
                    if((*ComIter)->CheckPopAdjListForPopulation(1))
                    {
                        (*ComIter)->IncreasePopulation();
                        freeWorker->SetEmployment((*ComIter));
                        freeGood->SetStore((*ComIter));
                        availableGoods-=1;
                        availableWorkers-=1;
                    }
                }
                else if((*ComIter)->GetPop() == 2)
                {
                    if((*ComIter)->CheckPopAdjListForPopulation(2))
                    {
                        (*ComIter)->IncreasePopulation();
                        freeWorker->SetEmployment((*ComIter));
                        freeGood->SetStore((*ComIter));
                        availableGoods-=1;
                        availableWorkers-=1;
                    }
                }
                else if((*ComIter)->GetPop() == 3)
                {
                    if((*ComIter)->CheckPopAdjListForPopulation(3))
                    {
                        (*ComIter)->IncreasePopulation();
                        freeWorker->SetEmployment((*ComIter));
                        freeGood->SetStore((*ComIter));
                        availableGoods-=1;
                        availableWorkers-=1;
                    }
                }
                else if((*ComIter)->GetPop() == 4)
                {
                    if((*ComIter)->CheckPopAdjListForPopulation(4))
                    {
                        (*ComIter)->IncreasePopulation();
                        freeWorker->SetEmployment((*ComIter));
                        freeGood->SetStore((*ComIter));
                        availableGoods-=1;
                        availableWorkers-=1;
                    }
                }
            }
    }
    for(ComIter = commercial_List.begin(); ComIter != commercial_List.end(); ComIter++)
        {
            (*ComIter)->UpdatePopulationList();
        }
}



void City::UpdateCity()
{
    UpdateCommercial();
    UpdateIndustrial();
    UpdateResidential();
   
}

void City::UpdateResidential()
{
    vector<Residential*>::iterator ResIter;
        for(ResIter = residential_List.begin(); ResIter != residential_List.end(); ResIter++)
        {
            
                if((*ResIter)->GetTotalPopulationAdj() == 0)
                {
                    if((*ResIter)->CheckPower())
                    {
                        (*ResIter)->IncreasePopulation();
                    }
                }
                else if((*ResIter)->GetPop() == 0)
                {
                    if((*ResIter)->CheckPopAdjListForPopulation(0))
                        {
                        
                            (*ResIter)->IncreasePopulation();
                        }
                }
                else if((*ResIter)->GetPop() == 1)
                {
                    if((*ResIter)->CheckPopAdjListForPopulation(1))
                    {
                        (*ResIter)->IncreasePopulation();
                    }
                }
                else if((*ResIter)->GetPop() == 2)
                {
                    if((*ResIter)->CheckPopAdjListForPopulation(2))
                    {
                        (*ResIter)->IncreasePopulation();
                    }
                }
                else if((*ResIter)->GetPop() == 3)
                {
                    if((*ResIter)->CheckPopAdjListForPopulation(3))
                    {
                        (*ResIter)->IncreasePopulation();
                    }
                }
                else if((*ResIter)->GetPop() == 4)
                {
                    if((*ResIter)->CheckPopAdjListForPopulation(4))
                    {
                        (*ResIter)->IncreasePopulation();
                    }
                }
    }
    for(ResIter = residential_List.begin(); ResIter != residential_List.end(); ResIter++ )
        {
            (*ResIter)->UpdatePopulationList();
        }

        CalcFreeWorkers();
}

void City::UpdateIndustrial() 
{
    Worker* worker1;
    Worker* worker2;
    vector<Residential*>::iterator ResIter;
    vector<Industrial*>::iterator IndIter;

        for(IndIter = industrial_List.begin(); IndIter != industrial_List.end(); IndIter++ )
        {
            for(ResIter = residential_List.begin(); ResIter != residential_List.end(); ResIter++)
        {
            if((*ResIter)->FindFreeWorker() != nullptr)
            {
                worker1 = (*ResIter)->FindFreeWorker();
                break;
            }

        }
        for(ResIter = residential_List.begin(); ResIter != residential_List.end(); ResIter++)
        {
            if((*ResIter)->FindFreeWorker() != nullptr)
            {
                worker2 = (*ResIter)->FindFreeWorker();
                if(worker2 == worker1)
                {
                    continue;
                }
                else{
                break;
                }
            }

        }
            if(availableWorkers > 1)
            {
                if((*IndIter)->GetTotalPopulationAdj() == 0 && (*IndIter)->GetPop() == 0)
                {
                    if((*IndIter)->CheckPower())
                    {
                        (*IndIter)->IncreasePopulation();
                        UpdatePollutionPropList(*IndIter);
                        worker1->SetEmployment((*IndIter));
                        worker2->SetEmployment((*IndIter));
                        availableWorkers-=2;
                    }
                }
                else if((*IndIter)->GetPop() == 0)
                {
                    if((*IndIter)->CheckPopAdjListForPopulation(0))
                        {
                        
                            (*IndIter)->IncreasePopulation();
                            UpdatePollutionPropList(*IndIter);
                            worker1->SetEmployment((*IndIter));
                            worker2->SetEmployment((*IndIter));
                            availableWorkers-=2;
                        }
                }
                else if((*IndIter)->GetPop() == 1)
                {
                    if((*IndIter)->CheckPopAdjListForPopulation(1) )
                    {
                        (*IndIter)->IncreasePopulation();
                        UpdatePollutionPropList(*IndIter);
                        worker1->SetEmployment((*IndIter));
                        worker2->SetEmployment((*IndIter));
                        availableWorkers-=2;
                    }
                }
                else if((*IndIter)->GetPop() == 2)
                {
                    if((*IndIter)->CheckPopAdjListForPopulation(2))
                    {
                        (*IndIter)->IncreasePopulation();
                        UpdatePollutionPropList(*IndIter);
                        worker1->SetEmployment((*IndIter));
                        worker2->SetEmployment((*IndIter));
                        availableWorkers-=2;
                    }
                }
                else if((*IndIter)->GetPop() == 3)
                {
                    if((*IndIter)->CheckPopAdjListForPopulation(3))
                    {
                        (*IndIter)->IncreasePopulation();
                        UpdatePollutionPropList(*IndIter);
                        worker1->SetEmployment((*IndIter));
                        worker2->SetEmployment((*IndIter));
                        availableWorkers-=2;
                    }
                }
                else if((*IndIter)->GetPop() == 4)
                {
                    if((*IndIter)->CheckPopAdjListForPopulation(4))
                    {
                        (*IndIter)->IncreasePopulation();
                        UpdatePollutionPropList(*IndIter);
                        worker1->SetEmployment((*IndIter));
                        worker2->SetEmployment((*IndIter));
                        availableWorkers-=2;
                    }
                }

    }
        }
    for(IndIter = industrial_List.begin(); IndIter != industrial_List.end(); IndIter++ )
        {
            (*IndIter)->UpdatePopulationList();
        }
        CalcFreeGoods();
}

void City::CalcPopulation()
{
    vector<Residential*>::iterator Resiter;
    int sum = 0;
    for(Resiter = residential_List.begin(); Resiter != residential_List.end(); Resiter++)
    {
       sum += (*Resiter)->GetPop();
    }

    vector<Industrial*>::iterator Inditer;
    for(Inditer = industrial_List.begin(); Inditer != industrial_List.end(); Inditer++ )
    {
        sum += (*Inditer)->GetPop();
    }

    vector<Commercial*>::iterator Comiter;
    for(Comiter = commercial_List.begin(); Comiter != commercial_List.end() ; Comiter++)
    {
        sum+=(*Comiter)->GetPop();
    }
    totalPopulation = sum;

}                    
void City::CalcPollution()
{
    vector<Cell*>::iterator iter;
    int sum = 0;
    for(iter = Cell_List.begin(); iter != Cell_List.end(); iter++)
    {
        sum+=(*iter)->GetPollution();
    }
    totalPollution = sum;
}               
void City::CalcFreeWorkers()
{
    vector<Residential*>::iterator Resiter;
    int sum = 0;
    for(Resiter = residential_List.begin(); Resiter != residential_List.end(); Resiter++)
    {
        sum += (*Resiter)->CountFreeWorkers();
    }
    availableWorkers = sum;
}
void City::CalcFreeGoods()
{
    vector<Industrial *>::iterator Inditer;
    int sum = 0;
    for(Inditer = industrial_List.begin(); Inditer != industrial_List.end(); Inditer++)
    {
        sum+=(*Inditer)->CountAvailableGoods();
    }
    availableGoods = sum;
}

void City::CalcGoods()
{
    int sum = 0;
    vector<Industrial*>::iterator Inditer;
    for(Inditer = industrial_List.begin(); Inditer != industrial_List.end(); Inditer++ )
    {
        sum += (*Inditer)->GetPop();
    }
    totalGoods = sum;
}

void City::CalcWorkers()
{
    vector<Residential*>::iterator Resiter;
    int sum = 0;
    for(Resiter = residential_List.begin(); Resiter != residential_List.end(); Resiter++)
    {
       sum += (*Resiter)->GetPop();
    }
    totalWorkers = sum;
}

int City::GetTotalPopulation(){
    return totalPopulation;
}

int City::GetTotalPollution()
{
    return totalPollution;
}
int City::GetTotalWorkers()
{
    return totalWorkers;
}
int City::GetTotalGoods()
{
    return totalGoods;
}
int City::GetTotalFreeGoods()
{
    return availableGoods;
}
int City::GetTotalFreeWorkers()
{
    return availableWorkers;
}
int City::GetMaxTime()
{
    return maxSteps;
}

int City::GetTimeStep()
{
    return timeStep;
}

int City::GetRefreshRate()
{
    return refreshRate;
}

void City::IncrementTimeStep()
{
    timeStep++;
}


void City::PopulateCellPopVec()
{
    vector<Industrial*>::iterator IndIter;
    vector<Commercial*>::iterator ComIter;
    vector<Residential*>::iterator ResIter;

    for(IndIter = industrial_List.begin(); IndIter != industrial_List.end(); IndIter++ )
        {
            (*IndIter)->PopulateAdjacencyPopList();
        }
     for(ResIter = residential_List.begin(); ResIter != residential_List.end(); ResIter++ )
        {
            (*ResIter)->PopulateAdjacencyPopList();
        }
    for(ComIter = commercial_List.begin(); ComIter != commercial_List.end(); ComIter++)
        {
            (*ComIter)->PopulateAdjacencyPopList();
        }
}

void City::DisplayCity(int first_x, int first_y, int second_x, int second_y)
{
    vector<Cell*> newList;
    vector<Cell*>::iterator cellIter1;
    vector<Cell*>::iterator cellIter2;
    for(cellIter1 = this->Cell_List.begin(); cellIter1 != this->Cell_List.end(); cellIter1++)
    {
        if(((*cellIter1)->GetX_Cord() >= first_x && (*cellIter1)->GetX_Cord() <= second_x) && ((*cellIter1)->GetY_Cord() >= first_y && (*cellIter1)->GetY_Cord() <= second_y))
        {
        newList.push_back(*cellIter1);
        }
    }

     vector<Cell *>::iterator iter;
    int count = 0, count2 = 0;
    int  resIndex = 0, comIndex = 0, indIndex = 0;
    int resPop = 0, comPop = 0, indPop = 0;
    cout << endl;
    cout << "Zoomed City Display:" << endl;
    cout << "| ";
    for(iter = newList.begin(); iter != newList.end(); iter++)
    {   
        Cell::Type control = (*iter)->GetType();
        count++;
        switch(control) //used to identify what kind of cell is being accessed and print the correct character
        {

            case Cell::Residential:
            {
                if(DisplayResidentialPopulation(resIndex) != 0)
                {
                    cout << DisplayResidentialPopulation(resIndex) << " | ";
                }
                else
                {
                    cout << 'R' << " | ";
                }
                resPop+=(*iter)->GetPop();
                resIndex++;
                break;
            }
            case Cell::Industrial:
            {
                if(DisplayIndustrialPopulation(indIndex) != 0)
                {
                    cout << DisplayIndustrialPopulation(indIndex) << " | ";
                }
                else
                {
                    cout << 'I' << " | ";
                }
                indIndex++;
                indPop+=(*iter)->GetPop();
                break;
            }
            case Cell::Commercial:
            {
                if(DisplayCommercialPopulation(comIndex) != 0)
                {
                    cout << DisplayCommercialPopulation(comIndex) << " | ";
                }
                else
                {
                    cout << 'C' << " | ";
                }
                comIndex++;
                comPop+=(*iter)->GetPop();
                break;
            }
            case Cell::PowerL:
            {
                cout << 'T' << " | ";
                break;
            }
            case Cell::PowerP:
            {   
                cout << 'P' << " | ";
                break;
            }
            case Cell::Combo:
            {
                cout << '#' << " | ";
                break;
            }
            case Cell::Road:
            {
                cout << '-' << " | ";
                break;
            }
            case Cell::Blank:
            {
                cout << ' ' << " | ";
                break;
            }
            
        }
        if( count == second_x-first_x + 1 && count2 != (second_y-first_y)) //formatting
        {
            count2++;
            cout << endl;
            cout << "| ";
            count = 0;
        }
    }
    cout << endl;
    int temppopulation = 0;
    for(iter = newList.begin(); iter != newList.end(); iter++)
    {
        temppopulation+=(*iter)->GetPop();
    }
    cout << "Total population for zoomed region: " << temppopulation << endl;
    cout << "Total residential population for zoomed region: " << resPop << endl;
    cout << "Total industrial population for zoomed region: " << indPop << endl;
    cout << "Total commercial population for zoomed region: " << comPop << endl;
    int temppollution = 0;
    for(iter = newList.begin(); iter != newList.end(); iter++)
    {
        temppollution+=(*iter)->GetPollution();
    }
    cout << "Total pollution for zoomed region: " << temppollution << endl;

}
    




int City::GetMax_X()
{
    return max_X;
}

int City::GetMax_Y()
{
    return max_Y;
}

void City::DisplayPollution() 
{
    vector<Cell *>::iterator iter;
    int count = 0, count2 = 0;
    int  resIndex = 0, comIndex = 0, indIndex = 0;
    cout << endl;
    cout << "FINAL STATE:" << endl;
    DisplayCity();
    cout << endl;
    cout << "FINAL POLLUTION STATE:" << endl;
    cout << "| ";
    for(iter = Cell_List.begin(); iter != Cell_List.end(); iter++)
    {   
        Cell::Type control = (*iter)->GetType();
        count++;
        switch(control) //used to identify what kind of cell is being accessed and print the correct character
        {

            case Cell::Residential:
            {
                if(DisplayResidentialPopulation(resIndex) != 0)
                {
                    cout << (*iter)->GetPollution() << " | ";
                }
                else
                {
                    cout << (*iter)->GetPollution()  << " | ";
                }
                resIndex++;
                break;
            }
            case Cell::Industrial:
            {
                if(DisplayIndustrialPopulation(indIndex) != 0)
                {
                    cout << (*iter)->GetPollution() << " | ";
                }
                else
                {
                    cout << (*iter)->GetPollution() << " | ";
                }
                indIndex++;
                break;
            }
            case Cell::Commercial:
            {
                if(DisplayCommercialPopulation(comIndex) != 0)
                {
                    cout << (*iter)->GetPollution() << " | ";
                }
                else
                {
                    cout << (*iter)->GetPollution()  << " | ";
                }
                comIndex++;
                break;
            }
            case Cell::PowerL:
            {
                cout << (*iter)->GetPollution()  << " | ";
                break;
            }
            case Cell::PowerP:
            {   
                cout << (*iter)->GetPollution()  << " | ";
                break;
            }
            case Cell::Combo:
            {
                cout << (*iter)->GetPollution()  << " | ";
                break;
            }
            case Cell::Road:
            {
                cout << (*iter)->GetPollution()  << " | ";
                break;
            }
            case Cell::Blank:
            {
                cout << (*iter)->GetPollution()  << " | ";
                break;
            }
            
        }
        if( count == max_X && count2 != max_Y - 1) //formatting
        {
            count2++;
            cout << endl;
            cout << "| ";
            count = 0;
        }
    }
    cout << endl;
}