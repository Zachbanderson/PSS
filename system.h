#ifndef SYSTEM_H
#define SYSTEM_H

#include "includes.h"
#include "scheduler.h"

using namespace std;

class System
{
public:
    System(std::map<string, Task*> &taskMap,
           std::map<string, std::map<string, vector<TimeBlock>>>& TBMap);
    ~System();

    /***************
     ** ACCESSORS **
     ***************/
    void displayMainMenu();
    void displayCreateMenu();
    void displayEditMenu();
    void displayDeleteMenu();

    void displayCalendar();


private:
    Scheduler* scheduler;

};

#endif // SYSTEM_H

/******************************
 ******** CONSTRUCTOR *********
 ******************************/

/****************************************************************
 * System();
 *   Constructor; Initialize class attributes
 *   Parameters: None
 *   Return: none
 ***************************************************************/

/***************
 ** ACCESSORS **
 ***************/

/*******************************************************************
 * void displayMainMenu();
 *
 *   Accessor; This method displays the main menu for the user
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void displayCreateMenu();
 *
 *   Accessor; This method displays the menu for creating a task
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void displayEditMenu();
 *
 *   Accessor; This method displays the menu for editing a task
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void displayDeleteMenu();
 *
 *   Accessor; This method displays the menu for deleting a task
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void displayCalendar();
 *
 *   Accessor; This method displays the calendar
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * bool validateTask(Task task);
 *
 *   Accessor; This method checks if a task's name and time are valid
 *------------------------------------------------------------------
 *   Parameter: task(Task)-Task to validate
 *------------------------------------------------------------------
 *   Return: bool-True if valid, false if not
 *******************************************************************/

/**************
 ** MUTATORS **
 **************/

/*******************************************************************
 * void readJSON(string fname);
 *
 *   Mutator; This method reads the specified JSON file
 *------------------------------------------------------------------
 *   Parameter: fname(string)-Name of the JSON file
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void writeJSON(string fname);
 *
 *   Mutator; This method writes to the specified JSON file
 *------------------------------------------------------------------
 *   Parameter: fname(string)-Name of the JSON file
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/
