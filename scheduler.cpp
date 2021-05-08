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
   double startTime, double duration, int intType, string endDate = "", int freq = 0 )
 {

   //check if time is valid
   if (timeValid(startDate, startTime, duration))
   {
     // create task
     if( intType >= 1 && intType <= 6)
     {

         return addRTask(RecurrentTask(name, startDate,startTime,
                          duration, Task::TaskTypes(intType), endDate, RecurrentTask::Frequency(1)));

     }
     else if(intType >= 7 && intType <=9)
    {
      //3- create task
      return addTTask(TransientTask(name, startDate,startTime,
                                        duration, Task::TaskTypes(intType)));

     }
   }
   else if(intType == 0)
   {
      return addATask(name, startDate,startTime, duration);

   }

   return true;
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
   string taskYear = boost::lexical_cast<string>(d.year());

   // Replace the instance of recurrent task with antiTask
   if(TimeBlockMap.find(taskYear) != TimeBlockMap.end())
   {
      if(timeBlockMap.at(taskYear).find(taskDate) != timeBlockMap.at(taskYear).end())
      {

         int tbArraySize = static_cast<int>(duration / 0.25);

         // find the index of the startTime in the timeBlock vector
         int indx = indexFinder(startTime);
         for(int i = indx; i < tbArraySize; i++)
         {
           if(timeBlockMap[taskYear][Date][i].getTask() != nullptr)
           {
             timeBlockMap[taskYear][Date][i].setTask(&task);

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
    else if(timeBlockMap.at(taskYear).find(sDate) == timeBlockMap.at(taskYear).end())
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
        if(timeBlockMap[taskYear][Date][i].getTask() != nullptr)
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
                    cout << it3->getStartTime() << " ";
                    cout << it3->getTask()->getName();
                    cout << endl;
                }

            }
        }
    }
}
