#ifndef ANTITASK_H
#define ANTITASK_H

#include "task.h"

class AntiTask : public Task
{
public:
	AntiTask();
	AntiTask(const std::string& newName, const std::string& newStartDate,					// name, startDate, startTime, duration, type = Cancellation
		double newStartTime, double newDuration)
		: Task(newName, newStartDate, newStartTime, newDuration, Task::Cancellation) {}

    void setType(int choice) override;
    void display() const override;			// print protected member variables
    ~AntiTask() override;
};

	/******************************
	******** CONSTRUCTOR *********
	******************************/

	/****************************************************************
	AntiTask(const std::string& newName, const std::string& newStartDate,
		double newStartTime, double newDuration, TaskTypes newType)
		: Task(newName, newStartDate, newStartTime, newDuration, Task::Cancellation) {}
	*   Constructor; Initialize class attributes using Task()
	*   Parameters:
	*		string newName - Name of the Task
	*		string newStartDate - Start Date of the Task
	*		double newStartTime - Start time of the Task
	*		double newDuration - Duration of the Task
	*		TaskTypes newType - Type of task (Always set to Cancellation)
	*   Return: none
	***************************************************************/

	/**************
	** MUTATORS **
	**************/

	/*******************************************************************
	* void setType(int choice);
	*
	*   Virtual Method; Change type of task (Compiler wanted this)
	*------------------------------------------------------------------
	*   Parameter: None
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
