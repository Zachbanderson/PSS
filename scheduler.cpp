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

    //printTimeBlockMap();
}


/**********************************************************
 *
 * Method createNewTask(): Class System
 *_________________________________________________________
 * This method takes user information for creating a new task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     name, startDate, startTime, duration, type is required for
 *    task Constructor
 *    endate and frequency is required for recurrent task if not mentioned
 *    will be defaulted to empty string and frequency of 0
 *
 * POST-CONDITIONS
 *     This function returns a pointer to the newly created task
 ***********************************************************/
 bool Scheduler::createNewTask(const string& name, const string& startDate,
   double startTime, double duration, int intType, string endDate, int freq)
{

    //cout << "Adding task" << endl;
    //check if time and name are valid
    boost::gregorian::date taskDate = boost::gregorian::date_from_iso_string(startDate);
    if (timeValid(taskDate, startTime, duration) && nameValid(name))
    {
        //cout << "Task is valid" << endl;
        // create task
        if( intType >= 1 && intType <= 6)
        {

            return addRTask(new RecurrentTask(name, startDate,startTime,
                          duration, Task::TaskTypes(intType), endDate,
                                       RecurrentTask::Frequency(freq)));
        }
        else if(intType >= 7 && intType <=9)
        {
            //3- create task
            return addTTask(new TransientTask(name, startDate,startTime,
                                        duration, Task::TaskTypes(intType)));
        }
    }
    else if(intType == 0)
    {
        return addATask(name, startDate, startTime, duration);
    }

    return false;
}

 /**********************************************************
  *
  * Method addATask(): Class Scheduler
  *_________________________________________________________
  * This method insert anti task in place of one instance of
  * Recurrent task
  *_________________________________________________________
  * PRE-CONDITIONS
  *     task(AntiTask)- Task to add in place of one instance of
  *     recurrent task that is supposed to be deleting
  *
  * POST-CONDITIONS
  *     This function returns true if it successfuly replaces
  *     the recurrent task inside the TimeBlockMap
  ***********************************************************/
 bool Scheduler::addATask(const std::string& name, const std::string& startDate,
   double startTime, double duration)    //Task to add
 {
   bool taskCreated = false;

   // if we successfuly null one instance of the recurrent task
   // then we will create antiTask and add it to the taskMap
   if(nullTimeBlockTask(name, startDate, startTime, duration))
   {
     // create anti task
     AntiTask task = AntiTask(name, startDate, startTime, duration );

     // save task into taskMap
     taskMap.insert(std::pair<string, Task*>(task.getName(), &task));
     taskCreated = true;
   }

     return taskCreated;
 }


 /**********************************************************
  *
  * Method nullTimeBlockTask(): Class Scheduler
  *_________________________________________________________
  * This method nulls the task on instance of
  * Recurrent task
  *_________________________________________________________
  * PRE-CONDITIONS
  *     startTime, startDate and duration of the recurrent task
  *
  * POST-CONDITIONS
  *     This function returns true if it successfuly nulls
  *     the task inside the TimeBlockMap
  ***********************************************************/
 bool Scheduler::nullTimeBlockTask(const string& name, const string& startDate, double startTime, double duration)
{
    bool completed = false;
    boost::gregorian::date taskDate = boost::gregorian::date_from_iso_string(startDate);
    string taskYear = boost::lexical_cast<string>(taskDate.year());
    string taskDay = boost::lexical_cast<string>(taskDate.day_of_year());

    if(TimeBlockMap.find(taskYear) != TimeBlockMap.end())
    {
        if(TimeBlockMap.at(taskYear).find(taskDay) != TimeBlockMap.at(taskYear).end())
        {
            int tbArraySize = static_cast<int>(duration / 0.25);

            // find the index of the starting time in the timeBlock vector
            int count = 0;
            int indx = indexFinder(startTime);
            int i = indx;
            for(i = indx; i < indx + tbArraySize; i++)
            {
                if(TimeBlockMap.at(taskYear).at(taskDay).at(i).getTask() != nullptr
                        && TimeBlockMap.at(taskYear).at(taskDay).at(i).getTask()->getName() == name)
                {
                    TimeBlockMap.at(taskYear).at(taskDay).at(i).setTask(nullptr);
                    count +=1 ;
                }
            }
            // check to see if all the timeBlocks associated with the task is deleted
            if (count == tbArraySize)
                {
                    //cout << count << " = number of timeblocks that were nulled." << endl;
                    completed = true;
                    // cout << "TimeBlocks associated with the task is also deleted " << endl;
                }
        }
        return completed;
    }

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
bool Scheduler::addTTask(TransientTask* task)    //Task to add
{
    //Reformat this to call validateTask instead
    if(addTaskToTimeBlockMap(task, task->getStartDate(), TimeBlockMap))
    {
        taskMap.insert(std::pair<string, Task*>(task->getName(), task));
        //cout << "Added to TimeBlockMap. Returning true" << endl;
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
bool Scheduler::addRTask(RecurrentTask* task)    //Task to add
{
    if(validateRTask(task))
    {
        taskMap.insert(std::pair<string, Task*>(task->getName(), task));
        for(boost::gregorian::date d = task->getStartDate(); d <= task->getEndDate(); d = d + date_duration(task->getFreq()))
        {
            //cout << "Date is: " << d << endl;
            addTaskToTimeBlockMap(task, d, TimeBlockMap);
        }
        return true;
    }
    return false;
}

/**********************************************************
 *
 * Method deleteTask(): Class Scheduler
 *_________________________________________________________
 * This method deletes a task by the given name
 *_________________________________________________________
 * PRE-CONDITIONS
 *     function requires the name of the task
 *
 * POST-CONDITIONS
 *     This function returns true if the task is successfuly deleted.
 ***********************************************************/
bool Scheduler::deleteTask(string taskName) //Task to delete
{
    bool deleted = false;

    // task attributes
    date startDate = date();
    double startTime = 0.0;
    double duration = 0;
    int type = 0;
    date endDate = date();
    int freq = 0;

    // Step 1 - find the task with the given name
    if(taskMap.find(taskName) != taskMap.end())
    {
        // Step 2 - get all the task attributes before deleting it
        std::map<string, Task*>::iterator it = taskMap.find(taskName);
        startDate = it->second->getStartDate();
        startTime = it->second->getStartTime();
        duration = it->second->getDuration();
        type = it->second->getTypeInt();

        // Step 3 -  if the task is recurrent, then find all associated dates
        if( type > 0  && type < 7)
        {
            RecurrentTask* rTask = static_cast<RecurrentTask*>(it->second);
            endDate = rTask->getEndDate();
            freq = rTask->getFreq();

            // get the number of days that the recurrent task will be repeating
            boost::gregorian::date_duration day_range = endDate - startDate;
            int numOfDays = day_range.days();
            boost::gregorian::date_duration f(freq);
            boost::gregorian::date sDate  = startDate ;

            for (int j = 0; j <= numOfDays; j += freq)
            {
                // Step 4 - use these dates to null the associated timeblocks
                nullTimeBlockTask(taskName, to_iso_string(sDate), startTime, duration);

                // Step 5 - use these dates  to find  associated AntiTask
                int count = 0;
                //std::map<string, Task*>::const_iterator it = taskMap.begin();
                for (std::map<string, Task*>::const_iterator it = taskMap.begin(); it != taskMap.end();)
                {
                    if( it->second->getStartDate() == sDate && it->second->getTypeInt() == 0)
                    {
                        if(( it->second->getStartTime() == startTime) && (it->second->getDuration() == duration))
                        {
                            // Step 6 - delete antiTask for sDate
                            it = taskMap.erase(it);
                            // Cout << "Anti tasks associated with the reucrrent task is also deleted" << endl;
                            count++;
                        }
                        else
                        {
                            ++it;
                        }
                    }
                    else
                    {
                        ++it;
                    }
                    
                }
                cout <<  "Number of AntiTask that is deleted is: " << count <<endl;
                // increment sDate = go to the next date of the recurrent task
                sDate  = sDate + f;
            }

            // Step 7 - delete the task
            taskMap.erase(taskName);
            deleted = true;
            // cout << "a recurrent task: " << name << "is deleted" <<endl;
        }
        // Step 8 - if task is transient
        else if (type > 6 && type < 10)
        {
            // Step 9 - use these dates to null the associated timeblocks
            nullTimeBlockTask(taskName, to_iso_string(startDate), startTime, duration);

            // Step 10 - delete the transient task
            taskMap.erase(taskName);
            deleted = true;
            // cout << "a transient task: " << name << "is deleted" <<endl;
        }
    }

    return deleted;
}

/**********************************************************
 *
 * Method getTask(): Class Scheduler
 *_________________________________________________________
 * This method checks if the name of a task is valid
 *_________________________________________________________
 * PRE-CONDITIONS
 *     taskName(string)- The name of the task to return
 *     taskDate(boost::gregorian::date) - The date the task is on
 *
 * POST-CONDITIONS
 *     This function returns a pointer to the task if found
 *     otherwise a nullpointer
 ***********************************************************/
Task* Scheduler::getTask(const string taskName, const string taskDate) const
{
    date date = date_from_iso_string(taskDate);
    string taskYear = boost::lexical_cast<string>(date.year());
    string taskDay = boost::lexical_cast<string>(date.day_of_year());
    if (TimeBlockMap.find(taskYear) == TimeBlockMap.end() || TimeBlockMap.at(taskYear).find(taskDay) == TimeBlockMap.at(taskYear).end())    //Year or day doesn't exist in timeblockmap
    {
        return nullptr;
    }
    else
    {
        vector<TimeBlock> dayVector = TimeBlockMap.at(taskYear).at(taskDay);
        for (vector<TimeBlock>::iterator iter = dayVector.begin(); iter != dayVector.end(); ++iter)
        {
            Task* checkTask = iter->getTask();
            try {
                if (checkTask != NULL && checkTask->getName() == taskName)  //Task exists for given timeblock
                {
                    return checkTask;
                }
            }
            catch (...) {
                cout << "Exceptionally couldn't find task.\n";
                return nullptr;
            }
        }
        return nullptr;
    }
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

/**********************************************************
 *
 * Method timeValid(): Class Scheduler
 *_________________________________________________________
 * This method checks if the date and time is available
 *_________________________________________________________
 * PRE-CONDITIONS
 *     SDate(string),  if date is not in the timeBlockMap it is
 *    available for new task -> return true
 *     startTime (double), if sTime is not in the map then
 *    it is avaialbe for the new task
 *     double duration, duration is need to find number of timeBlocks
 *
 * POST-CONDITIONS
 *     This function returns true if date and time is available
 *       for scheduling a new task
 ***********************************************************/

 bool Scheduler::timeValid(boost::gregorian::date date, double sTime, double duration)
 {
     bool valid = false;

     string taskYear = boost::lexical_cast<string>(date.year());
     string taskDay = boost::lexical_cast<string>(date.day_of_year());

   // if YEAR is not in the TimeBlockMap return true
     if(TimeBlockMap.find(taskYear) == TimeBlockMap.end())
     {
       valid = true;
     }
     // if the startDate is not in the timeBlockMap return true
     else if(TimeBlockMap.at(taskYear).find(taskDay) == TimeBlockMap.at(taskYear).end())
     {
       valid = true;
     }
     // if taskYear and taskDay is found then check timeBlocks
     else
     {
       // check if the timeBlocks are taken
       int tbArraySize = static_cast<int>(duration / 0.25);

       // find the index of the startTime in the timeBlock vector
       int indx = indexFinder(sTime);
       int countNull = 0;
       for(int i = indx; i < (tbArraySize + indx) ; i++)
       {
         if(TimeBlockMap.at(taskYear).at(taskDay).at(i).getTask() != nullptr)
         {
           valid = false;
         }
         else
         {
             countNull++;
         }
       }
       //cout << "count: " << countNull << endl;
       //cout << "arr: " << tbArraySize << endl;
       return countNull == tbArraySize ? true : false;
     }

     return valid;
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

                if(it3->getTask() != nullptr)
                {
                    cout << it3->tbGetStartTime() << " ";
                    cout << it3->getTask()->getName();
                    cout << endl;
                }

            }
        }
    }
}
