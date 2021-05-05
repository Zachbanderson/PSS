#ifndef RECURRENTTASK_H
#define RECURRENTTASK_H

#include "Task.h"

class RecurrentTask : public Task
{
public:
	enum Frequency
	{
		Daily = 1, Weekly = 7
	};

	RecurrentTask();
	RecurrentTask(const std::string& newName, const std::string& newStartDate,		//name, startDate, startTime, duration, type, endDate, freq
		double newStartTime, double newDuration, TaskTypes newType,
		const std::string& newEndDate, Frequency newFreq)
		: Task(newName, newStartDate, newStartTime, newDuration, newType) 
	{
		endDate = newEndDate;
		freq = newFreq;
	}

	// Accessors
	std::string getEndDate() const;
	int getFreq() const;									// returns frequency in integer form

	// Mutators
	void setEndDate(const std::string& newEndDate);			// set endDate of task
	void setFreq(int newFreq);								// set freq of task (only accepts 1 or 7)

	// Virtual stuff
	void setType(int choice);								// set type of task
	void display() const;									// print protected private member variablers

	~RecurrentTask();

private:
	std::string endDate;
	Frequency freq;
};

	/******************************
	******** CONSTRUCTOR *********
	******************************/

	/****************************************************************
	RecurrentTask(const std::string& newName, const std::string& newStartDate,	
		double newStartTime, double newDuration, TaskTypes newType,
		const std::string& newEndDate, Frequency newFreq)
		: Task(newName, newStartDate, newStartTime, newDuration, newType)
	*   Constructor; Initialize class attributes using Task()
	*   Parameters:
	*		string newName - Name of the Task
	*		string newStartDate - Start Date of the Task
	*		double newStartTime - Start time of the Task
	*		double newDuration - Duration of the Task
	*		TaskTypes newType - Type of task
	*		string newEndDate - End date of Task
	*		Frequency newFreq - frequency of Task
	*   Return: none
	***************************************************************/

	/***************
	** ACCESSORS **
	***************/

	/*******************************************************************
	* string getEndDate() const;
	*
	*   Accessor; Gets end date of task
	*------------------------------------------------------------------
	*   Parameter: None
	*------------------------------------------------------------------
	*   Return: string-End date of task
	*******************************************************************/

	/*******************************************************************
	* int getFreq() const;
	*
	*   Accessor; Gets the frequency of recurrent task
	*------------------------------------------------------------------
	*   Parameter: None
	*------------------------------------------------------------------
	*   Return: int-frequency of task in integer form
	*******************************************************************/

	/**************
	** MUTATORS **
	**************/

	/*******************************************************************
	* void setType(int choice);
	*
	*   Virtual Method; sets the TaskType of the task
	*------------------------------------------------------------------
	*   Parameter: choice(int)-The enum int to change the type to
	*------------------------------------------------------------------
	*   Return: none
	*******************************************************************/

	/*******************************************************************
	* void display() const;
	*
	*   Virtual Method; prints all protected member variables of the Task
	*------------------------------------------------------------------
	*   Parameter: None
	*------------------------------------------------------------------
	*   Return: none
	*******************************************************************/

#endif
