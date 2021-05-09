#include "system.h"

/**********************************************************
 *
 * Constructor System: Class System
 *_________________________________________________________
 * This method constructs the System class and reads the data
 * from the JSON file, populating the list of tasks
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will construct the System and load all
 *     tasks into memory
 ***********************************************************/
System::System(std::map<string, Task *> &taskMap,
               std::map<string, std::map<string, vector<TimeBlock> > > &TBMap)
{
    scheduler = new Scheduler(taskMap, TBMap);
}

/**********************************************************
 *
 * Method displayMainMenu(): Class System
 *_________________________________________________________
 * This method displays the main menu, sort of the main loop
 * of the program. From here, the user can choose to create,
 * delete, or edit a task, or see the calendar
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be created
 ***********************************************************/
void System::displayMainMenu()
{

}

/**********************************************************
 *
 * Method displayCreateMenu(): Class System
 *_________________________________________________________
 * This method displays the create menu, allowing the user to
 * create a task. A task is created if the actions are not cancelled
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be created
 ***********************************************************/
void System::displayCreateMenu()
{

}

/**********************************************************
 *
 * Method displayEditMenu(): Class System
 *_________________________________________________________
 * This method displays the edit menu, allowing the user to
 * edit a task. A task is edited if the actions are not cancelled
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be created
 ***********************************************************/
void System::displayEditMenu()
{

}

/**********************************************************
 *
 * Method displayDeleteMenu(): Class System
 *_________________________________________________________
 * This method displays the delete menu, allowing the user to
 * delete a task. A task is deleted if the actions are not cancelled
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be deleted
 ***********************************************************/
void System::displayDeleteMenu()
{

}

/**********************************************************
 *
 * Method displayCalendar(): Class System
 *_________________________________________________________
 * This method displays the calendar, allowing the user to
 * see his/her tasks laid out
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void System::displayCalendar()
{

}
