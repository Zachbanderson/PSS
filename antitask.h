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
	AntiTask& operator=(const AntiTask& otherTask);

    void setType(int choice) override;
    void display() const override;			// print protected member variables
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

	/**********************************************************
	*
	* Constructor AntiTask(const AntiTask& otherTask): Class AntiTask
	*_________________________________________________________
	* This method is the copy constructor for the AntiTask class
	*_________________________________________________________
	* PRE-CONDITIONS
	*     otherTask: The task to copy from
	*
	* POST-CONDITIONS
	*     This function will construct a AntiTask class
	***********************************************************/

	/**********************************************************
	*
	* Overloaded Assignment operator=(const AntiTask& otherTask): Class AntiTask
	*_________________________________________________________
	* This method assigns an instance of AntiTask to another
	*_________________________________________________________
	* PRE-CONDITIONS
	*     otherTask: The task to copy from
	*
	* POST-CONDITIONS
	*     This function will assign the right hand variable to a copy of the left
	***********************************************************/

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
