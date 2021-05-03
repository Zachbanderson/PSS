#include <iostream>
#include "task.h"

using namespace std;

Task::Task()
{
	name = "N/A";
	startDate = "00000000";
	startTime = 00.00;
	duration = 00.00;
	type = Class;
}

Task::Task(const std::string& newName, const std::string& newStartDate,
	double newStartTime, double newDuration, TaskTypes newType)
{
	name = newName;
	startDate = newStartDate;
	startTime = newStartTime;
	duration = newDuration;
	type = newType;
}

string Task::getName() const
{
	return name;
}

string Task::getStartDate() const
{
	return startDate;
}

double Task::getStartTime() const
{
	return startTime;
}

double Task::getDuration() const
{
	return duration;
}

void Task::setName(const string& newName)
{
	name = newName;
}

void Task::setStartDate(const string& newStartDate)
{
	startDate = newStartDate;
}

void Task::setStartTime(double newStartTime)
{
	startTime = newStartTime;
}

void Task::getDuration(double newDuration)
{
	duration = newDuration;
}

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

void Task::display() const
{
	cout << "This is a [normal] Task" << endl;
	cout << "Name: " << name << endl;
	cout << "Start Date: " << startDate << endl;
	cout << "Start Time: " << startTime << endl;
	cout << "Duration: " << duration << endl;
    cout << "Type: " << getType() << endl;
}

string Task::serialize() const
{
    return "{\"Name\":\"" + name + "\",\"Date\":" + startDate +
            ",\"Type\":\"" + getType() + "\",\"StartTime\":" + to_string(startTime)
            + ",\"Duration\":" + to_string(duration) + "}";
}

Task::~Task()
{

}
