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

     cout << "Adding task" << endl;
    //check if time and name are valid
    if (timeValid(startDate, startTime, duration) && nameValid(name))
    {
        cout << "Task is valid" << endl;
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
   // create anti task
   AntiTask task = AntiTask(name, startDate, startTime, duration );

   // save task into taskMap
   taskMap.insert(std::pair<string, Task*>(task.getName(), &task));

   // convert string startDate to a date
   boost::gregorian::date taskDate = date_from_iso_string(startDate);
   string taskYear = boost::lexical_cast<string>(taskDate.year());
   string taskDay = boost::lexical_cast<string>(taskDate.day());

   // Replace the instance of recurrent task with antiTask
   if(TimeBlockMap.find(taskYear) != TimeBlockMap.end())
   {
      if(TimeBlockMap.at(taskYear).find(taskDay) != TimeBlockMap.at(taskYear).end())
      {

         int tbArraySize = static_cast<int>(duration / 0.25);

         // find the index of the startTime in the timeBlock vector
         int indx = indexFinder(startTime);
         for(int i = indx; i < tbArraySize; i++)
         {
           if(TimeBlockMap.at(taskYear).at(taskDay).at(i).getTask() != nullptr)
           {
             TimeBlockMap.at(taskYear).at(taskDay).at(i).setTask(nullptr);

           }
         }
       }
     }

     return false;
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
        cout << "Added to TimeBlockMap. Returning true" << endl;
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
        for(boost::gregorian::date d = task->getStartDate();
            d <= task->getEndDate(); d = d + date_duration(task->getFreq()))
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
  bool completed = false;
  // task attributes
  string startDate;
  double startTime = 0.0;
  double duration = 0;

  if(taskMap.find(taskName) != taskMap.end())
  {
      std::map<string, Task*>::iterator it = taskMap.find(taskName);
      startDate = it->second->getStartDateString();
      startTime = it->second->getStartTime();
      duration = it->second->getDuration();
      taskMap.erase(taskName);
      // cout << "task: " << name << "is deleted" <<endl;
  }

  // Look for any antiTask with the same date, time and duration
  for (std::map<string, Task*>::const_iterator it = taskMap.begin(); it != taskMap.end(); ++it)
  {

     if(( it->second->getStartDate() == date_from_iso_string(startDate)) && ( it->second->getStartTime() == startTime)
        && (it->second->getDuration() == duration))
         {
           // delete antiTask
           taskMap.erase(it->first);
         }
         // Cout << "Anti tasks associated with the reucrrent task is also deleted" << endl;
  }

  boost::gregorian::date taskDate = boost::gregorian::date_from_iso_string(startDate);
  string taskYear = boost::lexical_cast<string>(taskDate.year());

  if(TimeBlockMap.find(taskYear) != TimeBlockMap.end())
  {
     if(TimeBlockMap.at(taskYear).find(startDate) != TimeBlockMap.at(taskYear).end())
     {

        int tbArraySize = static_cast<int>(duration / 0.25);

        // find the index of the starting time in the timeBlock vector
        int count = 0;
        int indx = indexFinder(startTime);
        for(int i = indx; i < tbArraySize; i++)
        {
          if(TimeBlockMap.at(taskYear).at(startDate).at(i).getTask() != nullptr)
          {
            TimeBlockMap.at(taskYear).at(startDate).at(i).setTask(nullptr);
            count +=1 ;
          }
        }
        // check to see if all the timeBlocks associated with the task is deleted
        if (count == tbArraySize - 1)
          {
            completed = true;
            // cout << "TimeBlocks associated with the task is also deleted " << endl;
          }
      }
  }

  return completed;
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

bool Scheduler::timeValid(string sDate, double sTime, double duration)
{
  // convert string startDate to a date
    boost::gregorian::date d = boost::gregorian::date_from_iso_string(sDate);
    string taskYear = boost::lexical_cast<string>(d.year());

  // if YEAR is not in the TimeBlockMap return true
    if(TimeBlockMap.find(taskYear) == TimeBlockMap.end())
    {
      return true;
    }
    // if the startDate is not in the timeBlockMap return true
    else if(TimeBlockMap.at(taskYear).find(sDate) == TimeBlockMap.at(taskYear).end())
    {
      return true;
    }
    // if time slot is available return true
    else
    {
      // check if the timeBlocks are taken
      int tbArraySize = static_cast<int>(duration / 0.25);

      // find the index of the startTime in the timeBlock vector
      int indx = indexFinder(sTime);
      for(int i = indx; i < tbArraySize; i++)
      {
        if(TimeBlockMap.at(taskYear).at(sDate).at(i).getTask() != nullptr)
        {
          return false;
        }
      }
    }
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
