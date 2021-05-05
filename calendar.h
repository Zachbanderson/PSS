#ifndef CALENDAR_H
#define CALENDAR_H
#include <iostream>
#include "task.h"
#include "timeblock.h"

class Calendar
{
    vector<TimeBlock> timeBlockList;  //Vector of timeblocks within the Calendar

public:

    Calendar();
    //Create vector of timeblocks --option: either return array or directly write to JSON
    vector<TimeBlock> createArrayOfTimeBlock(Task* task, double taskStartTime);
    vector<boost::gregorian::date> createDateArrayForRecurrentTask(Task* task, int numOfDays);
    void createTimeBlocksForTask(Task* task);

    //Possibly have antitask to remove timeblocks OR calendar will remove timeblocks

    void writeToFile();             //Write timeblocks to JSON 
    void readFromFile();            //Read timeblocks from JSON
    void timeBlockDisplay();        //Print timeblocks from JSON
    // Task getTask(string name);       //don't need 
    // bool nameAvailable(Task task);   //dont need, System does this
    bool dateAvailable(string date);    //date to check if available
    bool timeAvailable(float time);    //starting time to check if available
};

#endif // CALENDAR_H

