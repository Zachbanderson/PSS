#ifndef TRANSIENTTASK_H
#define TRANSIENTTASK_H

#include "Task.h"

class TransientTask : public Task
{
public:
	TransientTask();
	TransientTask(const std::string& newName, const std::string& newStartDate,		//name, startDate, startTime, duration, type
		double newStartTime, double newDuration, TaskTypes newType)
		: Task(newName, newStartDate, newStartTime, newDuration, newType) {}

	void setType(int choice);		// set type of task
	void display() const;			// print protected member variables

	~TransientTask();
};

	/******************************
	******** CONSTRUCTOR *********
	******************************/

	/****************************************************************
	TransientTask(const std::string& newName, const std::string& newStartDate,		
		double newStartTime, double newDuration, TaskTypes newType)
		: Task(newName, newStartDate, newStartTime, newDuration, newType) {}
	*   Constructor; Initialize class attributes using Task()
	*   Parameters:
	*		string newName - Name of the Task
	*		string newStartDate - Start Date of the Task
	*		double newStartTime - Start time of the Task
	*		double newDuration - Duration of the Task
	*		TaskTypes newType - Type of task
	*   Return: none
	***************************************************************/

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
