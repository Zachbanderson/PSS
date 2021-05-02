#include <iostream>
#include "AntiTask.h"

using namespace std;

AntiTask::AntiTask()
{
	type = Cancellation;
}

AntiTask::~AntiTask()
{

}

void AntiTask::setType(int choice)
{
	type = Cancellation;
}

void AntiTask::display() const
{
	cout << "This is a [AntiTask] Task" << endl;
	cout << "Name: " << name << endl;
	cout << "Start Date: " << startDate << endl;
	cout << "Start Time: " << startTime << endl;
	cout << "Duration: " << duration << endl;
	cout << "Type: " << getType() << endl;
}