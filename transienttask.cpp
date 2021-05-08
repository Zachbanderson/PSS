#include <iostream>
#include "transienttask.h"

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
 * Constructor TransientTask(const TransientTask& otherTask): Class TransientTask
 *_________________________________________________________
 * This method is the copy constructor for the TransientTask class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     otherTask: The task to copy from
 *
 * POST-CONDITIONS
 *     This function will construct a TransientTask class
 ***********************************************************/

TransientTask::TransientTask(const TransientTask& otherTask) : 
	Task(otherTask.name, otherTask.startDate, otherTask.startTime,
	otherTask.duration, otherTask.type)
{

}

/**********************************************************
 *
 * Overloaded Assignment operator=(const TransientTask& otherTask): Class TransientTask
 *_________________________________________________________
 * This method assigns an instance of TransientTask to another
 *_________________________________________________________
 * PRE-CONDITIONS
 *     otherTask: The task to copy from
 *
 * POST-CONDITIONS
 *     This function will assign the right hand variable to a copy of the left
 ***********************************************************/

TransientTask& TransientTask::operator=(const TransientTask& otherTask)
{
	this->~TransientTask();
	name = otherTask.name;
	startDate = otherTask.startDate;
	startTime = otherTask.startTime;
	duration = otherTask.duration;
	type = otherTask.type;
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
