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
                     string fname, date start, date end);  //File to write to
    void displayCalendar(string date, int rangeOfDays,
                         std::map<string, std::map<string,
                         vector<TimeBlock>>> &TBMap);

    /**************
     ** MUTATORS **
     **************/
    std::map<string, Task*> readFromFile(std::map<string, std::map<string, vector<TimeBlock>>> &TBMap, string fname); //JSON file with data

    /**********************************************************
	*
	* Method convertDoubleToString(double time): Class Calendar
	*_________________________________________________________
	* This method converts American time in a double
    * (ex. 3:15 AM) into a string
	* that our program can work with
	*_________________________________________________________
	* PRE-CONDITIONS
	*     time: a double
	*
	* POST-CONDITIONS
	*     This function returns the time rounded to the nearest as a
	*	   24-hour system rounded to the nearest .15 for minutes
	***********************************************************/
	std::string Calendar::convertDoubleToString(double time);

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

