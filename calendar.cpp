#include <stdexcept>
#include "boost/Date_Time.hpp"
#include "calendar.h"

using namespace std;
//TO-DO: Load from JSON file into memory
//TO-DO: Make function addTask (diff function for transient/recurrent tasks
//          to add task to the map in the JSON

Calendar::Calendar()
{

}
//TO-DO: Just create time blocks in memory
vector<TimeBlock> createTimeBlocks(Task* task)
{
    //Check type of task
    float increment = 0.25;
    int tbArraySize = static_cast<int>(task->getDuration() / increment);
    float startTime = task->getStartTime();
    vector <TimeBlock> tbVector; 

    for (int i = 0; i <= tbArraySize; i++)
    {
        TimeBlock tb(newTask1, startTime);
        tbVector.push_back(tb);
        startTime += increment;
    }

    return tbVector; 

}

void Calendar::writeToFile()
{

}

// Create map<year<date<timeblocks>>> from JSON file
void Calendar::readFromFile()
{

}

void Calendar::timeBlockDisplay() 
{

}

bool Calendar::dateAvailable(string data)
{
    return false;
}

bool Calendar::timeAvailable(float time)
{
    return false;
}
