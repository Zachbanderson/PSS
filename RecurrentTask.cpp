#include <iostream>
#include "RecurrentTask.h"

using namespace std;

RecurrentTask::RecurrentTask()
{
	freq = Daily;
}

void RecurrentTask::setType(int choice)
{
	if (choice < 1 || choice > 6)
	{
		cout << "The input you've entered is not a Transient Task" << endl;
		return;
	}
	else
	{
		type = static_cast<Task::TaskTypes>(choice);
	}
}

string RecurrentTask::getEndDate() const
{
	return endDate;
}

int RecurrentTask::getFreq() const
{
	return static_cast<int>(freq);
}

void RecurrentTask::setEndDate(const string& newEndDate)
{
	endDate = newEndDate;
}

void RecurrentTask::setFreq(int newFreq)
{
	freq = static_cast<RecurrentTask::Frequency>(newFreq);
}

void RecurrentTask::display() const
{
	cout << "This is a [Recurrent] Task" << endl;
	cout << "Name: " << name << endl;
	cout << "Start Date: " << startDate << endl;
	cout << "End Date: " << endDate << endl;
	cout << "Start Time: " << startTime << endl;
	cout << "Duration: " << duration << endl;
	cout << "Frequency: " << static_cast<int>(freq) << endl;
    cout << "Type: " << getType() << endl;
}

string RecurrentTask::serialize() const
{
    return "{\"Name\":\"" + name + "\",\"StartDate\":" + startDate +
            ",\"Type\":\"" + getType() + "\",\"StartTime\":" +
            to_string(startTime) + ",\"Duration\":" + to_string(duration)
            + ",\"EndDate\":" + endDate + ",\"Frequency\":" +
            to_string(static_cast<int>(freq)) + "}";
}

RecurrentTask::~RecurrentTask()
{

}
