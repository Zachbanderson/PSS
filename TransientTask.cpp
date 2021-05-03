#include <iostream>
#include "transienttask.h"

using namespace std;

TransientTask::TransientTask()
{
	
}

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

void TransientTask::display() const
{
	cout << "This is a [Transient] Task" << endl;
	cout << "Name: " << name << endl;
	cout << "Start Date: " << startDate << endl;
	cout << "Start Time: " << startTime << endl;
	cout << "Duration: " << duration << endl;
    cout << "Type: " << getType() << endl;
}

TransientTask::~TransientTask()
{

}
