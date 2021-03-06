#include <iostream>
#include "RecurrentTask.h"

using namespace std;

/**********************************************************
 *
 * Constructor RecurrentTask: Class RecurrentTask
 *_________________________________________________________
 * This method is the default constructor for the RecurrentTask class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will construct an RecurrentTask class
 ***********************************************************/

RecurrentTask::RecurrentTask()
{
	freq = Daily;
}

/**********************************************************
 *
 * Method setType(int choice): Class RecurrentTask
 *_________________________________________________________
 * This method sets the type of RecurrentTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     choice: what to change into
 *
 * POST-CONDITIONS
 *     Turns the type of RecurrentTask into specified type.
 *	   Valid types at TaskTypes 1-6
 ***********************************************************/

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

/**********************************************************
 *
 * Method getEndDate() const: Class RecurrentTask
 *_________________________________________________________
 * This method displays the endDate of RecurrentTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Returns endDate
 ***********************************************************/

string RecurrentTask::getEndDate() const
{
	return endDate;
}

/**********************************************************
 *
 * Method getFreq() const: Class RecurrentTask
 *_________________________________________________________
 * This method displays the freq of RecurrentTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Returns freq
 ***********************************************************/

int RecurrentTask::getFreq() const
{
	return static_cast<int>(freq);
}

/**********************************************************
 *
 * Method setEndDate(string newEndDate) const: Class RecurrentTask
 *_________________________________________________________
 * This method modifies the endDate of RecurrentTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     newEndDate: The new end date to set
 *
 * POST-CONDITIONS
 *     Nothing
 ***********************************************************/

void RecurrentTask::setEndDate(const string& newEndDate)
{
	endDate = newEndDate;
}

/**********************************************************
 *
 * Method setFreq(int newFreq) const: Class RecurrentTask
 *_________________________________________________________
 * This method modifies the freq of RecurrentTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     newFreq: the frequency to change into.
 *
 * POST-CONDITIONS
 *     Nothing
 ***********************************************************/


void RecurrentTask::setFreq(int newFreq)
{
	if (newFreq == 1 || newFreq == 7)
		freq = static_cast<RecurrentTask::Frequency>(newFreq);
}

/**********************************************************
 *
 * Method display() const: Class RecurrentTask
 *_________________________________________________________
 * This method displays the information of RecurrentTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     None
 *
 * POST-CONDITIONS
 *     Prints the name, start date, end date, start time,
 *	   duration, frequency and type of task
 ***********************************************************/

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

/**********************************************************
 *
 * Destructor RecurrentTask: Class RecurrentTask
 *_________________________________________________________
 * This method is the destructor for the RecurrentTask
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will destroy a RecurrentTask
 ***********************************************************/

RecurrentTask::~RecurrentTask()
{

}
