#ifndef RECURRENTTASK_H
#define RECURRENTTASK_H

#include "task.h"

using std::string;

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
        const std::string newEndDate, Frequency newFreq)
		: Task(newName, newStartDate, newStartTime, newDuration, newType) 
	{
        endDate = date_from_iso_string(newEndDate);
		freq = newFreq;
	}

	// Accessors
    date getEndDate() const;
	int getFreq() const;									// returns frequency in integer form

	// Mutators
    void setEndDate(const std::string& newEndDate);			// set endDate of task
	void setFreq(int newFreq);								// set freq of task (only accepts 1 or 7)

	// Virtual stuff
    void setType(int choice) override;                      // set type of task
    void display() const override;                          // print protected private member variablers
    string serialize() const override;

    ~RecurrentTask() override{}

private:
    date endDate;
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

    /*******************************************************************
    * virtual string serialize() const;
    *
    *   Virtual Method; serializes information into a json string
    *------------------------------------------------------------------
    *   Parameter: None
    *------------------------------------------------------------------
    *   Return: string-serialized task information
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
