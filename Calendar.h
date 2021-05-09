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

public:

    Calendar();

    //Possibly have antitask to remove timeblocks OR calendar will remove timeblocks

    /***************
     ** ACCESSORS **
     ***************/
    void writeToFile(std::map<string, Task*> taskMap,   //Tasks to write
                     string fname);  //File to write to
    void displayCalendar(string date, int rangeOfDays,
                         std::map<string, std::map<string,
                         vector<TimeBlock>>> &TBMap);

    /**************
     ** MUTATORS **
     **************/
    std::map<string, Task*> readFromFile(std::map<string, std::map<string, vector<TimeBlock>>> &TBMap, string fname); //JSON file with data

private:
    string dataName = "data.json";      //Output file name


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

