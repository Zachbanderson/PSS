#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "includes.h"
#include "calendar.h"

using namespace std;
using boost::gregorian::date;

class Scheduler
{
public:
    Scheduler(std::map<string, Task*> &taskMap, std::map<string, std::map<string, vector<TimeBlock>>>& TBMap);

    bool addTTask(TransientTask task);
    bool addRTask(RecurrentTask task);
    bool deleteTTask(string taskName);
    bool deleteRTask(string taskName);
    //TODO: Tell Rachel and Kevin that the editTask function in the menu should
    //just call deleteTask and then addTask


private:
    std::map<string, Task*> taskMap;
    std::map<string, std::map<string, vector<TimeBlock>>> TimeBlockMap;

    bool validateTask(Task* task);  //Task to validate
    bool nameValid(string name);    //Name of the task. Checks if name is in
                                    //taskMap
    bool timeValid(Task* task);     //Task to check the time of

    //bool addTaskToTimeBlockMap(Task* t, date d);
    //vector<TimeBlock> createTimeBlocks(Task* task);

    void printTimeBlockMap();
};

#endif // SCHEDULER_H
