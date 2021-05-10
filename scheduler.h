#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "includes.h"
#include "calendar.h"

using namespace std;
using boost::gregorian::date;

class Scheduler
{
public:
    Scheduler(std::map<string, Task*> &taskMap,
              std::map<string, std::map<string, vector<TimeBlock>>>& TBMap);

    /***************
     ** ACCESSORS **
     ***************/
    std::map<string, Task*> getTaskMap();
    std::map<string, std::map<string, vector<TimeBlock>>> getTBMap()
    {return TimeBlockMap;}
    Task* getTask(const string taskName, const string taskDate) const;
    bool nameValid(string name);    //Name of the task. Checks if name is in
                                    //taskMap
    bool timeValid(double sDate, double sTime, double duration); //if date and time available return true

    /**************
     ** MUTATORS **
     **************/
    bool createNewTask(const string& name, const string& startDate,
                       double startTime, double duration, int type,
                       string endDate = "", int freq = 0 );
    bool addTask(Task* task);
    bool addTTask(TransientTask* task);
    bool addRTask(RecurrentTask* task);
    bool deleteTask(string taskName);
    bool addATask(const std::string& name, const std::string& startDate,
      double startTime, double duration);
    bool nullTimeBlockTask(const string& startDate, double startTime, double duration);


private:
    std::map<string, Task*> taskMap;
    std::map<string, std::map<string, vector<TimeBlock>>> TimeBlockMap;


    /***************
     ** ACCESSORS **
     ***************/
    bool validateTTask(TransientTask* ttask);   //Task to validate
    bool validateRTask(RecurrentTask* rtask);   //Task to validate



    void printTimeBlockMap();
};

#endif // SCHEDULER_H

/******************************
 ******** CONSTRUCTOR *********
 ******************************/

/****************************************************************
 * Scheduler();
 *   Constructor; Initialize class attributes
 *   Parameters: taskMap(std::map<string, Task*>&) - Predefined map of tasks
 *               TBMap(std::map<string, std::map<string, vector<TimeBlock>>>&)
 *               - Map of tasks and TimeBlocks
 *   Return: none
 ***************************************************************/

/***************
 ** ACCESSORS **
 ***************/

/*******************************************************************
 * std::map<string, Task*> getTaskMap();
 *
 *   Accessor; This method returns the taskMap
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: std::map<string, Task*>
 *******************************************************************/

/*******************************************************************
 * bool validateTTask(TransientTask* ttask);
 *
 *   Accessor; This method checks if a task is able to be added
 *------------------------------------------------------------------
 *   Parameter: ttask(TransientTask*) - Task to add
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * bool validateTTask(RecurrentTask* rtask);
 *
 *   Accessor; This method checks if a task is able to be added
 *------------------------------------------------------------------
 *   Parameter: rtask(RecurrentTask*) - Task to add
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * bool nameValid(string name);
 *
 *   Accessor; This method checks if the task name is unique
 *------------------------------------------------------------------
 *   Parameter: name(string) - Name to check
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * bool timeValid(date d);
 *
 *   Accessor; This method checks if a task date is valid
 *------------------------------------------------------------------
 *   Parameter: d(boost::gregorian::date) - Date to check
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * void printTimeBlockMap();
 *
 *   Accessor; This method prints the TimeBlocks in the TimeBlockMap
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/**************
 ** MUTATORS **
 **************/

/*******************************************************************
 * bool addTTask(Task* task);
 *
 *   Mutator; This method adds a transient task to the taskMap and the
 *   TimeBlockMap
 *------------------------------------------------------------------
 *   Parameter: task(TransientTask*) - Task to add
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * bool addRTask(Task* task);
 *
 *   Mutator; This method adds a recurrent task to the taskMap and the
 *   TimeBlockMap
 *------------------------------------------------------------------
 *   Parameter: task(RecurrentTask*) - Task to add
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * bool deleteTTask(string taskName);
 *
 *   Mutator; This method deletes a transient task from the taskMap and the
 *   TimeBlockMap
 *------------------------------------------------------------------
 *   Parameter: taskName(string) - Name of the task to delete
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * bool deleteRTask(string taskName);
 *
 *   Mutator; This method deletes a recurrent task from the taskMap and the
 *   TimeBlockMap
 *------------------------------------------------------------------
 *   Parameter: taskName(string) - Name of the task to delete
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/

/*******************************************************************
 * bool cancelRTask(AntiTask task);
 *
 *   Mutator; This method creates an AntiTask that cancels out a recurrent task
 *------------------------------------------------------------------
 *   Parameter: task(AntiTask) - AntiTask to add
 *------------------------------------------------------------------
 *   Return: bool
 *******************************************************************/
