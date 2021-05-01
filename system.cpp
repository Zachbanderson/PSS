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
System::System()
{
    readJSON("stuff.json");
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

/**********************************************************
 *
 * Method validateTask(): Class System
 *_________________________________________________________
 * This method checks the name and timespan of a task to see
 * if it is valid
 *_________________________________________________________
 * PRE-CONDITIONS
 *     task(Task) - Task to validate
 *
 * POST-CONDITIONS
 *     This function returns true if the task is valid. False
 *     otherwise
 ***********************************************************/
bool System::validateTask(Task task)
{
    return true;
}

/**********************************************************
 *
 * Method readJSON(): Class System
 *_________________________________________________________
 * This method reads the JSON file that stores task data and
 * populates the tasks vector. Called at startup, should not
 * be called anywhere else
 *_________________________________________________________
 * PRE-CONDITIONS
 *     fname(string) - Name of the file with all the JSON data
 *
 * POST-CONDITIONS
 *     This function populates the tasks vector. Returns nothing
 ***********************************************************/
void System::readJSON(string fname)
{

}

/**********************************************************
 *
 * Method writeJSON(): Class System
 *_________________________________________________________
 * This method extracts all tasks from the tasks vector and
 * writes it to a JSON file specified by fname
 *_________________________________________________________
 * PRE-CONDITIONS
 *     fname(string) - Name of the file to write the JSON data
 *
 * POST-CONDITIONS
 *     This function writes all the data in the tasks vector
 *     to a file. Returns nothing
 ***********************************************************/
void System::writeJSON(string fname)
{

}
