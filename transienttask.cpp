#include <iostream>
#include "TransientTask.h"

using namespace std;


/**********************************************************
 *
 * Constructor TransientTask: Class TransientTask
 *_________________________________________________________
 * This method is the default constructor for the TransientTask class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will construct a TransientTask class
 ***********************************************************/

TransientTask::TransientTask()
{
	
}

/**********************************************************
 *
 * Method setType(int choice): Class TransientTask
 *_________________________________________________________
 * This method sets the type of TransientTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     choice: what to change into 
 *
 * POST-CONDITIONS
 *     Turns the type of TransientTask into specified type.
 *	   Valid types are TaskTypes 7-9
 ***********************************************************/

void TransientTask::setType(int choice)
{
	if (choice < 7 || choice > 9)
	{
		cout << "The input you've entered is not a Transient Task" << endl;
		return;
	}
	else
	{
		type = static_cast<Task::TaskTypes>(choice);
	}
}

/**********************************************************
 *
 * Method display() const: Class TransientTask
 *_________________________________________________________
 * This method displays the information of TransientTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Prints the name, start date, start time, duration, and type
 ***********************************************************/

void TransientTask::display() const
{
	cout << "This is a [Transient] Task" << endl;
	cout << "Name: " << name << endl;
	cout << "Start Date: " << startDate << endl;
	cout << "Start Time: " << startTime << endl;
	cout << "Duration: " << duration << endl;
	cout << "Type: " << getType() << endl;
}

/**********************************************************
 *
 * Destructor TransientTask: Class TransientTask
 *_________________________________________________________
 * This method is the destructor for the TransientTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will destroy an TransientTask
 ***********************************************************/

TransientTask::~TransientTask()
{

}
