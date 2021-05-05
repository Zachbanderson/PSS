#ifndef CALENDAR_H
#define CALENDAR_H

#include "includes.h"
#include "json.hpp"

using namespace std;
using nlohmann::json;

class Calendar
{
    vector<TimeBlock> timeBlockList;  //Vector of timeblocks within the Calendar

public:

    Calendar();
    ~Calendar();
    
    vector<TimeBlock> createTimeBlocks(Task* task);  //Create vector of timeblocks --option: either return array or directly write to JSON

    //Possibly have antitask to remove timeblocks OR calendar will remove timeblocks

    void writeToFile();             //Write timeblocks to JSON 
    void readFromFile();            //Read timeblocks from JSON
    void timeBlockDisplay();        //Print timeblocks from JSON
    // Task getTask(string name);       //don't need 
    // bool nameAvailable(Task task);   //dont need, System does this
    bool dateAvailable(string date);    //date to check if available
    bool timeAvailable(float time);    //starting time to check if available
    void printTasks();

private:
    std::map<string, Task*> taskMap;    //Stores the tasks
    //Used to check if a task is valid
    std::map<string, std::map<string, TimeBlock>> validMap;
    string dataName = "data.json";

    int convertTypeToInt(string type);
};

#endif // CALENDAR_H

