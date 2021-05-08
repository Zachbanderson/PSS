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
 * Constructor AntiTask(const AntiTask& otherTask): Class AntiTask
 *_________________________________________________________
 * This method is the copy constructor for the AntiTask class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     otherTask: The task to copy from
 *
 * POST-CONDITIONS
 *     This function will construct a AntiTask class
 ***********************************************************/

AntiTask::AntiTask(const AntiTask& otherTask) :
	Task(otherTask.name, otherTask.startDate, otherTask.startTime,
		otherTask.duration, otherTask.type)
{

}

/**********************************************************
 *
 * Overloaded Assignment operator=(const AntiTask& otherTask): Class AntiTask
 *_________________________________________________________
 * This method assigns an instance of AntiTask to another
 *_________________________________________________________
 * PRE-CONDITIONS
 *     otherTask: The task to copy from
 *
 * POST-CONDITIONS
 *     This function will assign the right hand variable to a copy of the left
 ***********************************************************/

AntiTask& AntiTask::operator=(const AntiTask& otherTask)
{
	this->~AntiTask();
	name = otherTask.name;
	startDate = otherTask.startDate;
	startTime = otherTask.startTime;
	duration = otherTask.duration;
	type = otherTask.type;
}

/**********************************************************
 *
 * Destructor AntiTask: Class Antitask
 *_________________________________________________________
 * This method is the destructor for the AntiTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will destroy an AntiTask
 ***********************************************************/

AntiTask::~AntiTask()
{

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
