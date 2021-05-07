#include "scheduler.h"

Scheduler::Scheduler(std::map<string, Task*> &taskMap, std::map<string, std::map<string, vector<TimeBlock>>> &TBMap)
{
    cout << "In scheduler constructor" << endl;
    this->taskMap = taskMap;
    TimeBlockMap = TBMap;
//    for(std::map<string, Task*>::iterator it = this->taskMap.begin();
//        it != this->taskMap.end(); it++)
//    {
//        cout << "In for loop" << endl;
//        cout << "Adding task " << it->first << endl;
//        if(it->second->getType() == "Exercise")
//        {
////            RecurrentTask* r = it->second;
////            for(boost::gregorian::date d = r->getStartDate();
////                d <= it->second->getEndDate(); d = d + date_duration(frequency))
////            {
////                //cout << "Date is: " << d << endl;
////                addTaskToValid(r, d, map);
////            }
//            addRTask(*it->second);
//        }
//        addTaskToTimeBlockMap(it->second, it->second->getStartDate());
//    }
    printTimeBlockMap();
}

bool Scheduler::addTTask(TransientTask task)    //Task to add
{
    //addTaskToTimeBlockMap(task, task.getDate());
}

bool Scheduler::addRTask(RecurrentTask task)    //Task to add
{

}

bool Scheduler::deleteTTask(string taskName) //Task to delete
{

}

bool Scheduler::deleteRTask(string taskName) //Task to delete
{

}

bool Scheduler::validateTask(Task *task)    //Task to validate
{

}

bool Scheduler::nameValid(string name)  //Name of the new task
{

}

bool Scheduler::timeValid(Task *task)   //Task to check if the time is valid
{

}

//bool Scheduler::addTaskToTimeBlockMap(Task *task, date date)
//{
//    string taskYear = boost::lexical_cast<string>(date.year());
//    string taskDay = boost::lexical_cast<string>(date.day_of_year());

//    //If we haven't found a task with this year yet
//    if(TimeBlockMap.find(taskYear) == TimeBlockMap.end())
//    {
//        cout << "Haven't found the year" << endl;
//        //Inserting a blank map at the year mark
//        TimeBlockMap.insert(std::pair<string, std::map<string,
//                            vector<TimeBlock>>>(taskYear, std::map<string,
//                                                vector<TimeBlock>>()));
//        cout << "Inserted " << taskYear << endl;
//        cout << "Inserted " << taskDay << " at " << taskYear << endl;
//        //Creating a vector of 96 empty TimeBlocks at the day of the year
//        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
//                                         (taskDay, createTimeBlocks(task)));
//        cout << "Added the TimeBlocks" << endl;

//    }
//    //If the year is in the map but the day isn't
//    else if(TimeBlockMap.at(taskYear).find(taskDay) == TimeBlockMap.at(taskYear).end())
//    {
//        cout << "Haven't found the day" << endl;
//        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
//                                         (taskDay, createTimeBlocks(task)));
//        cout << "Inserted " << taskDay << " at " << taskYear << endl;
//        cout << "Added the TimeBlocks" << endl;
//    }

//    //Call function to populate TimeBlocks here. Have the function return true
//    //if it can be added. False otherwise
//    //cout << task->getStartTime() << endl;



//    ///validMap.at(taskYear).at(taskDay).populate(start, end);


//    //Returning false means that the task wasn't added
//    return false;
//}

//vector<TimeBlock> Scheduler::createTimeBlocks(Task *task)
//{
//    //Check type of task
//    float increment = 0.25;
//    double taskStartTime = task->getStartTime();
//    int tbArraySize = static_cast<int>(task->getDuration() / increment);
//    double timeBlockStartTime = 0.0;
//    vector <TimeBlock> tbVector;

//    for (int i = 0, j = 0; i <= 96; i++)
//    {
//        if (timeBlockStartTime == taskStartTime && j < tbArraySize)
//        {

//            TimeBlock tb(task, taskStartTime);
//            tbVector.push_back(tb);

//            //cout << taskStartTime << endl;
//            timeBlockStartTime += increment;
//            taskStartTime += increment;
//            j++;
//        }
//        else
//        {
//            TimeBlock tb(nullptr, taskStartTime);
//            tbVector.push_back(tb);
//            timeBlockStartTime += increment;
//        }

//    }

//    return tbVector;
//}

void Scheduler::printTimeBlockMap()
{
    cout << "In printTimeBlockMap" << endl;
    for(std::map<string, std::map<string, vector<TimeBlock>>>::iterator it =
        TimeBlockMap.begin(); it != TimeBlockMap.end(); it++)
    {
        cout << "In first for" << endl;
        for(std::map<string, vector<TimeBlock>>::iterator it2 = it->second.begin();
            it2 != it->second.end(); it2++)
        {
            cout << "In second for" << endl;
            cout << "On day " << it2->first << endl;
            for(std::vector<TimeBlock>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
            {
                cout << "In third for" << endl;
                cout << it3->get_tb_startTime() << " ";
            }
            cout << endl;
        }
    }
}
