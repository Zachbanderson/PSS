#include "scheduler.h"


/**********************************************************
 *
 * Constructor(): Class Scheduler
 *_________________________________________________________
 * Constructor: initializes class attributes
 *_________________________________________________________
 * PRE-CONDITIONS
 *     taskMap(std::map<string, Task*>&)- Map of pre-defined tasks
 *     TBMap(std::map<string, std::map<string, vector<TimeBlock>>>&) pre-defined
 *     map of tasks with their TimeBlocks
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
Scheduler::Scheduler(std::map<string, Task*> &taskMap,  //Map of tasks
                     std::map<string, std::map<string, vector<TimeBlock>>>
                     &TBMap)            //Map of TimeBlocks
{
    //cout << "In scheduler constructor" << endl;
    this->taskMap = taskMap;
    TimeBlockMap = TBMap;

    printTimeBlockMap();
}

/**********************************************************
 *
 * Method addTTask(): Class Scheduler
 *_________________________________________________________
 * This method checks if the name of a task is valid
 *_________________________________________________________
 * PRE-CONDITIONS
 *     task(TransientTask)- Task to add
 *
 * POST-CONDITIONS
 *     This function returns nothing. Adds the TransientTask
 *     to TimeBlockMap
 ***********************************************************/
bool Scheduler::addTTask(TransientTask task)    //Task to add
{
    //Reformat this to call validateTask instead
    if(addTaskToTimeBlockMap(&task, task.getStartDate(), TimeBlockMap))
    {
        taskMap.insert(std::pair<string, Task*>(task.getName(), &task));
        return true;
    }
    return false;
}

/**********************************************************
 *
 * Method addRTask(): Class Scheduler
 *_________________________________________________________
 * This method checks if the name of a task is valid
 *_________________________________________________________
 * PRE-CONDITIONS
 *     task(RecurrentTask)- Task to add
 *
 * POST-CONDITIONS
 *     This function returns nothing. Adds the recurrent task
 *     to TimeBlockMap
 ***********************************************************/
void Scheduler::addRTask(RecurrentTask task)    //Task to add
{
    if(validateRTask(&task))
    {
        for(boost::gregorian::date d = task.getStartDate();
            d <= task.getEndDate(); d = d + date_duration(task.getFreq()))
        {
            //cout << "Date is: " << d << endl;
            addTaskToTimeBlockMap(&task, d, TimeBlockMap);
        }
    }

}

bool Scheduler::deleteTTask(string taskName) //Task to delete
{

}

bool Scheduler::deleteRTask(string taskName) //Task to delete
{

}

bool Scheduler::cancelRTask(AntiTask task)  //Task to represent a cancelled
{

}

std::map<string, Task *> Scheduler::getTaskMap()
{
    return taskMap;
}

bool Scheduler::validateRTask(RecurrentTask *rtask)
{
    if(nameValid(rtask->getName()))
    {
        return true;
    }
}

bool Scheduler::validateTTask(TransientTask *ttask)    //Task to validate
{
    if(nameValid(ttask->getName()))
    {
        return true;
    }
}

/**********************************************************
 *
 * Method nameValid(): Class Scheduler
 *_________________________________________________________
 * This method checks if the name of a task is valid
 *_________________________________________________________
 * PRE-CONDITIONS
 *     name(string)- Name of the new Task to check
 *
 * POST-CONDITIONS
 *     This function returns true if the task is already in
 *     the taskMap
 ***********************************************************/
bool Scheduler::nameValid(string name)  //Name of the new task
{
    //If the name is not in the taskMap
    if(taskMap.find(name) == taskMap.end())
    {
        return true;
    }
    return false;
}

bool Scheduler::timeValid(date d)   //Task to check if the time is valid
{

}


/**********************************************************
 *
 * Method printTimeBlockMap(): Class Scheduler
 *_________________________________________________________
 * This method prints the TimeBlocks and the tasks associated
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing. Prints the tasks in the TimeBlockMap
 ***********************************************************/
void Scheduler::printTimeBlockMap()
{
    cout << "In printTimeBlockMap" << endl;
    for(std::map<string, std::map<string, vector<TimeBlock>>>::iterator it =
        TimeBlockMap.begin(); it != TimeBlockMap.end(); it++)
    {
        //cout << "In first for" << endl;
        cout << "In year " << it->first << endl;
        for(std::map<string, vector<TimeBlock>>::iterator it2 =
            it->second.begin();
            it2 != it->second.end(); it2++)
        {
//            cout << "In second for" << endl;
            cout << "On day " << it2->first << endl;
            for(std::vector<TimeBlock>::iterator it3 = it2->second.begin();
                it3 != it2->second.end(); it3++)
            {
                //cout << "In third for" << endl;

                if(it3->get_task() != nullptr)
                {
                    cout << it3->get_tb_startTime() << " ";
                    cout << it3->get_task()->getName();
                    cout << endl;
                }

            }
        }
    }
}
