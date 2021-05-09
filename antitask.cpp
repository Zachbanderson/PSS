#include <iostream>
#include "antitask.h"

using namespace std;

/**********************************************************
 *
 * Constructor AntiTask: Class Antitask
 *_________________________________________________________
 * This method is the default constructor for the AntiTask class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will construct an AntiTask class
 ***********************************************************/

AntiTask::AntiTask()
{
	type = Cancellation;
}

/**********************************************************
 *
 * Method setType(int choice): Class AntiTask
 *_________________________________________________________
 * This method sets the type of AntiTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     choice: what to change into (Not actually needed)
 *
 * POST-CONDITIONS
 *     Turns the type of Antitask into Cancellation
 *	   This function is here mainly because setType() is virtual
 ***********************************************************/

void AntiTask::setType(int choice)
{
	type = Cancellation;
}

/**********************************************************
 *
 * Method display() const: Class AntiTask
 *_________________________________________________________
 * This method displays the information of AntiTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Prints the name, start date, start time, duration, and type
 ***********************************************************/

void AntiTask::display() const
{
	cout << "This is a [AntiTask] Task" << endl;
	cout << "Name: " << name << endl;
	cout << "Start Date: " << startDate << endl;
	cout << "Start Time: " << startTime << endl;
	cout << "Duration: " << duration << endl;
	cout << "Type: " << getType() << endl;
}
