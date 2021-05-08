#include <iostream>
#include "task.h"

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
    	startDate = date();
	startTime = 00.00;
	duration = 00.00;
	type = Class;
}

/**********************************************************
 *
 * Constructor Task(const Task& otherTask): Class Task
 *_________________________________________________________
 * This method is the copy constructor for the Task class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     otherTask: The task to copy from
 *
 * POST-CONDITIONS
 *     This function will construct a Task class
 ***********************************************************/

Task::Task(const Task& otherTask)
{
	name = otherTask.name;
	startDate = otherTask.startDate;
	startTime = otherTask.startTime;
	duration = otherTask.duration;
	type = otherTask.type;
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
    startDate = date_from_iso_string(newStartDate);
	startTime = newStartTime;
	duration = newDuration;
	type = newType;
}

/**********************************************************
 *
 * Overloaded Assignment operator=(const Task& otherTask): Class Task
 *_________________________________________________________
 * This method assigns an instance of Task to another
 *_________________________________________________________
 * PRE-CONDITIONS
 *     otherTask: The task to copy from
 *
 * POST-CONDITIONS
 *     This function will assign the right hand variable to a copy of the left
 ***********************************************************/

Task& Task::operator=(const Task& otherTask)
{
	this->~Task();
	name = otherTask.name;
	startDate = otherTask.startDate;
	startTime = otherTask.startTime;
	duration = otherTask.duration;
	type = otherTask.type;
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

date Task::getStartDate() const
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

void Task::setStartDate(const date newStartDate)
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
	case Class:
		return "Class";
	case Study:
		return "Study";
	case Sleep:
		return "Sleep";
	case Exercise:
		return "Exercise";
	case Work:
		return "Work";
	case Meal:
		return "Meal";
	case Visit:
		return "Visit";
	case Shopping:
		return "Shopping";
	case Appointment:
		return "Appointment";
	default:
		return "Error";
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
 * Method serialize(): Class Recurrent______________________________
 * This method serializes the task information to JSON string
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     string-Formats the Name, Date, Type, StartTime, and
 *     Duration as a JSON string
 ***********************************************************/
string Task::serialize() const
{
    return "{\"Name\":\"" + name + "\",\"Date\":" +
            to_iso_string(startDate) + ",\"Type\":\"" + getType() +
            "\",\"StartTime\":" + to_string(startTime) + ",\"Duration\":" +
            to_string(duration) + "}";
}

/**********************************************************
 *
 * Method convertTimeToDouble(int hour, int minutes, string abbreviation): Class ???
 *_________________________________________________________
 * This method converts American time (ex. 3:15 AM) into a double
 * that our program can work with
 *_________________________________________________________
 * PRE-CONDITIONS
 *     hour: the hour of time
 *     minutes: the minutes of the time
 *     abbreviation: AM/PM, must be capitalized (please)
 *
 * POST-CONDITIONS
 *     This function returns the time rounded to the nearest as a
 *	   24-hour system rounded to the nearest .15 for minutes
 ***********************************************************/

double Task::convertTimeToDouble(int hour, int minutes, const string& abbreviation)
{
	if (hour == 12)
	{
		hour = 0;
	}
	if (abbreviation == "PM")
	{
		hour += 12;
	}
	double minsRounded = (double(((minutes + 15 / 2) / 15) * 15)) / 60;

	return hour + minsRounded;
}
