#include <iostream>
#include "Task.h"

using namespace std;

/**********************************************************
 *
 * Constructor Task(): Class Task
 *_________________________________________________________
 * This method is the default constructor for the Task class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will construct a Task class
 ***********************************************************/

Task::Task()
{
	name = "N/A";
	startDate = "00000000";
	startTime = 00.00;
	duration = 00.00;
	type = Class;
}

/**********************************************************
 *
 * Constructor Task(const std::string& newName, const std::string& newStartDate,
	double newStartTime, double newDuration, TaskTypes newType): Class Task
 *_________________________________________________________
 * This method is the overloaded constructor for the Task class
 *_________________________________________________________
 * PRE-CONDITIONS
 *		newName: name of task
 *		newStartDate: start date of task
 *		newStartTime: start time of task
 *		newDuration: duration of task
 *		newType: type of task
 *
 * POST-CONDITIONS
 *     This function will construct a Task class
 ***********************************************************/

Task::Task(const std::string& newName, const std::string& newStartDate,
	double newStartTime, double newDuration, TaskTypes newType)
{
	name = newName;
	startDate = newStartDate;
	startTime = newStartTime;
	duration = newDuration;
	type = newType;
}

/**********************************************************
 *
 * Method getName() const: Class Task
 *_________________________________________________________
 * This method displays the name of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Returns name
 ***********************************************************/

string Task::getName() const
{
	return name;
}

/**********************************************************
 *
 * Method getStartDate() const: Class Task
 *_________________________________________________________
 * This method displays the start date of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Returns startDate
 ***********************************************************/

string Task::getStartDate() const
{
	return startDate;
}

/**********************************************************
 *
 * Method getStartTime() const: Class Task
 *_________________________________________________________
 * This method displays the start time of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Returns startTime
 ***********************************************************/

double Task::getStartTime() const
{
	return startTime;
}

/**********************************************************
 *
 * Method getDuration() const: Class Task
 *_________________________________________________________
 * This method displays the duration of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Returns duration
 ***********************************************************/

double Task::getDuration() const
{
	return duration;
}

/**********************************************************
 *
 * Method setName(string newName): Class Task
 *_________________________________________________________
 * This method modifies the name of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     newName: the new name of the task
 *
 * POST-CONDITIONS
 *     Nothing
 ***********************************************************/

void Task::setName(const string& newName)
{
	name = newName;
}

/**********************************************************
 *
 * Method setStartDate(string newStartDate): Class Task
 *_________________________________________________________
 * This method modifies the start date of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     newStartDate: the new start date
 *
 * POST-CONDITIONS
 *     Nothing
 ***********************************************************/

void Task::setStartDate(const string& newStartDate)
{
	startDate = newStartDate;
}

/**********************************************************
 *
 * Method setStartTime(double newStartTime): Class Task
 *_________________________________________________________
 * This method modifies the start time of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     newStartTime: the new start time
 *
 * POST-CONDITIONS
 *     Nothing
 ***********************************************************/

void Task::setStartTime(double newStartTime)
{
	startTime = newStartTime;
}

/**********************************************************
 *
 * Method setDuration(double newDuration): Class Task
 *_________________________________________________________
 * This method modifies the duration of Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     newDuration: the new duration 
 *
 * POST-CONDITIONS
 *     Nothing
 ***********************************************************/

void Task::setDuration(double newDuration)
{
	duration = newDuration;
}

/**********************************************************
 *
 * Method getType() const: Class Task
 *_________________________________________________________
 * This method returns the type of Task as a string
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Returns the type of task as a string
 ***********************************************************/

string Task::getType() const
{
	switch (type)
	{
	case Cancellation:
		return "Cancellation";
		break;
	case Class:
		return "Class";
		break;
	case Study:
		return "Study";
		break;
	case Sleep:
		return "Sleep";
		break;
	case Exercise:
		return "Exercise";
		break;
	case Work:
		return "Work";
		break;
	case Meal:
		return "Meal";
		break;
	case Visit:
		return "Visit";
		break;
	case Shopping:
		return "Shopping";
		break;
	case Appointment:
		return "Appointment";
		break;
	default:
		return "Error";
		break;
	}
}

/**********************************************************
 *
 * Method display() const: Class Task
 *_________________________________________________________
 * This method displays the information of tTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Prints the name, start date, end date, start time,
 *	   duration, frequency and type of task
 ***********************************************************/

void Task::display() const
{
	cout << "This is a [normal] Task" << endl;
	cout << "Name: " << name << endl;
	cout << "Start Date: " << startDate << endl;
	cout << "Start Time: " << startTime << endl;
	cout << "Duration: " << duration << endl;
	cout << "Type: " << getType() << endl;
}

/**********************************************************
 *
 * Destructor Task: Class Task
 *_________________________________________________________
 * This method is the destructor for the Task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will destroy a Task
 ***********************************************************/

Task::~Task()
{

}
