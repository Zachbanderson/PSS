#ifndef CALENDAR_H
#define CALENDAR_H

#include "includes.h"
#include "json.hpp"
#include "helpers.h"

using namespace std;
using nlohmann::json;
using boost::gregorian::date;

class Calendar
{
    vector<TimeBlock> timeBlockList;  //Vector of timeblocks within the Calendar

public:

    Calendar();
    //~Calendar();
    
    vector<TimeBlock> createTimeBlocks(Task* task);  //Create vector of timeblocks --option: either return array or directly write to JSON

    //Possibly have antitask to remove timeblocks OR calendar will remove timeblocks

    /***************
     ** ACCESSORS **
     ***************/
    void writeToFile(std::map<string, Task*> taskMap,   //Tasks to write
                     string fname);  //File to write to

    void timeBlockDisplay();        //Print timeblocks from JSON
    // Task getTask(string name);       //don't need 
    // bool nameAvailable(Task task);   //dont need, System does this
    bool dateAvailable(string date);    //date to check if available
    bool timeAvailable(float time);    //starting time to check if available
    //void printTasks();
    //void printValid(std::map<string, std::map<string, vector<TimeBlock>>>&);

    /**************
     ** MUTATORS **
     **************/
    std::map<string, Task*> readFromFile(std::map<string, std::map<string, vector<TimeBlock>>> &TBMap, string fname); //JSON file with data

private:
    //std::map<string, Task*> taskMap;    //Stores the tasks
    //Used to check if a task is valid

    //TODO: Change validMap name to TimeBlockMap
    //std::map<string, std::map<string, TimeBlock>> validMap;
    string dataName = "data.json";      //Output file name

    //int convertTypeToInt(string type);  //Task type

    /**************
     ** MUTATORS **
     **************/

    //bool addTaskToValid(Task*, date, std::map<string, std::map<string, vector<TimeBlock>>>&);      //Date of the task to add to the validation
                                    //map. Rejected if invalid
};

#endif // CALENDAR_H


/***************
 ** ACCESSORS **
 ***************/

/*******************************************************************
 * void writeToFile();
 *
 *   Accessor; This method writes the tasks to a file output
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void printTasks();
 *
 *   Accessor; This method displays the tasks in the calendar
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/**************
 ** MUTATORS **
 **************/

/*******************************************************************
 * void readFromFile();
 *
 *   Mutator; This method reads the tasks from a file
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * bool addTaskToValid(date);
 *
 *   Mutator; This method reads the tasks from a file
 *------------------------------------------------------------------
 *   Parameter: date(boost::gregorian::date)-Date of the task
 *------------------------------------------------------------------
 *   Return: bool-True if date is valid. False otherwise
 *******************************************************************/
