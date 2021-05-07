#ifndef TASK_H
#define TASK_H

#include <string>
#include "boost/date_time.hpp"

using namespace boost::gregorian;

class Task
{
public:
	enum TaskTypes
	{
		Cancellation = 0, Class = 1, Study = 2, Sleep = 3, Exercise = 4,
		Work = 5, Meal = 6, Visit = 7, Shopping = 8, Appointment = 9
	};

	// Default Constructor
	Task();

	// Overloaded Constructor
	Task(const std::string& newName, const std::string& newStartDate,	//name, startDate, startTime, duration, type
		double newStartTime, double newDuration, TaskTypes newType);

	/***************
	 ** ACCESSORS **
	 ***************/
	std::string getName() const;
    date getStartDate() const;
	double getStartTime() const;
	double getDuration() const;
	std::string getType() const;
    virtual void display() const;							// print protected member variables
    virtual std::string serialize() const;

	/**************
	 ** MUTATORS **
	 **************/
	void setName(const std::string& newName);				// set name of task
    void setStartDate(const date newStartDate);		// set start date of task
	void setStartTime(double newStartTime);					// set start time of task
    void setDuration(double newDuration);					// set duration of task
	virtual void setType(int choice) = 0;					// set type of task


    virtual ~Task() {}

protected:
    std::string name;       //Name of the task
    date startDate;         //Date the task starts
    double startTime;       //Time the task starts
    double duration;        //How long the task lasts
    TaskTypes type;         //The type of the task
};

	/******************************
	******** CONSTRUCTOR *********
	******************************/

	/****************************************************************
	* Task((const std::string& newName, const std::string& newStartDate,
	double newStartTime, double newDuration, TaskTypes newType);
	*   Constructor; Initialize class attributes
	*   Parameters: 
	*		string newName - Name of the Task
	*		string newStartDate - Start Date of the Task
	*		double newStartTime - Start time of the Task
	*		double newDuration - Duration of the Task
	*		TaskTypes newType - Type of task
	*   Return: none
	***************************************************************/

	/***************
	** ACCESSORS **
	***************/

	/*******************************************************************
	* string getName() const;
	*
	*   Accessor; This method gets the name of the Task
	*------------------------------------------------------------------
	*   Parameter: none
	*------------------------------------------------------------------
	*   Return: string-Name of Task
	*******************************************************************/

	/*******************************************************************
	* string getStartDate() const;
	*
	*   Accessor; This method gets the start date of the Task
	*------------------------------------------------------------------
	*   Parameter: none
	*------------------------------------------------------------------
	*   Return: string-Start date of the Task
	*******************************************************************/

	/*******************************************************************
	* double getStartTime() const;
	*
	*   Accessor; This method gets the start time of the Task
	*------------------------------------------------------------------
	*   Parameter: none
	*------------------------------------------------------------------
	*   Return: double-Start time of the Task
	*******************************************************************/

	/*******************************************************************
	* double getDuration() const;
	*
	*   Accessor; This method gets the duration of the Task
	*------------------------------------------------------------------
	*   Parameter: none
	*------------------------------------------------------------------
	*   Return: double-duration of the Task
	*******************************************************************/

	/*******************************************************************
	* string getDuration() const;
	*
	*   Accessor; This method gets the task type of the Task
	*------------------------------------------------------------------
	*   Parameter: none
	*------------------------------------------------------------------
	*   Return: string-name of TaskType in string form of the Task
	*******************************************************************/

    /*******************************************************************
    * virtual void display() const;
    *
    *   Virtual Method; prints all protected member variables of the Task
    *------------------------------------------------------------------
    *   Parameter: None
    *------------------------------------------------------------------
    *   Return: none
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
	* void setName(const std::string& newName);
	*
	*   Method; This method sets the name of the Task
	*------------------------------------------------------------------
	*   Parameter: newName(string) - The name to be changed into
	*------------------------------------------------------------------
	*   Return: none
	*******************************************************************/

	/*******************************************************************
	* void setStartDate(const std::string& newName);
	*
	*   Method; This method sets the name of the Task
	*------------------------------------------------------------------
	*   Parameter: newName(string) - The name to be changed into
	*------------------------------------------------------------------
	*   Return: none
	*******************************************************************/

	/*******************************************************************
	* void setStartTime(double newStartTime);
	*
	*   Method; This method sets the start time 
	*------------------------------------------------------------------
	*   Parameter: newStartTime(double) - The new start time
	*------------------------------------------------------------------
	*   Return: none
	*******************************************************************/

	/*******************************************************************
	* void getDuration(double newDuration);
	*
	*   Method; This method sets the duration
	*------------------------------------------------------------------
	*   Parameter: newStartTime(double) - The new duration
	*------------------------------------------------------------------
	*   Return: none
	*******************************************************************/

	/*******************************************************************
	* virtual void setType(int choice) = 0;
	*
	*   Virtual Method; sets the TaskType of the task
	*------------------------------------------------------------------
	*   Parameter: choice(int)-The enum int to change the type to
	*------------------------------------------------------------------
	*   Return: none
	*******************************************************************/
#endif
