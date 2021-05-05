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
vector<TimeBlock> createArrayOfTimeBlock(Task* task, double taskStartTime)
{
    //Check type of task
    float increment = 0.25;
    int tbArraySize = static_cast<int>(task->getDuration() / increment);
    double timeBlockStartTime = 0.0;
    vector <TimeBlock> tbVector; 

    for (int i = 0, j = 0; i <= 96; i++)
    {
        if (timeBlockStartTime == taskStartTime && j < tbArraySize)
        {
           
            TimeBlock tb(task, taskStartTime);
            tbVector.push_back(tb);

            //cout << taskStartTime << endl;
            timeBlockStartTime += increment;
            taskStartTime += increment;
            j++;
        }
        else
        {
            TimeBlock tb(nullptr, taskStartTime);
            tbVector.push_back(tb);
            timeBlockStartTime += increment;
        }

    }


    return tbVector; 

}

void Calendar::createTimeBlocksForTask(Task* task)
{
    //Check type of task
    int type = task->getTypeInt();
    float taskStartTime = task->getStartTime();

    // if task is transient
    if (type == 1 || type == 2 || type == 3 || type == 4 || type == 5 || type == 6)
    {

        
        vector <TimeBlock> tbVector = createArrayOfTimeBlock(task, taskStartTime);
    }
    // task is recurrent
    else if (type == 7 || type == 8 || type == 9)
    {
        string taskStartDate = task->getStartDate();
        string taskEndDate = task->getEndDate();

        // Converting ISO Format (YYYYMMDD) String to date object
        boost::gregorian::date d1 = boost::gregorian::date_from_iso_string(taskStartDate);
        boost::gregorian::date d2 = boost::gregorian::date_from_iso_string(taskEndDate);

        // get number of days that the recurrent task is repeating
        boost::gregorian::date_duration day_range = d2 - d1;  


        // cast the number of days ( duration of dates format) to integer
        int numOfDays = day_range.days();
        for (int i = 0; i < numOfDays; i++)
        {

            vector <TimeBlock> tbVector = createArrayOfTimeBlock(task, taskStartTime);
            vector<boost::gregorian::date> dates = createDateArrayForRecurrentTask( task, numOfDays, d1);
        }
    }
    else
    {
        cerr << "The task type is unrecognized." << endl;
    }

}


vector<boost::gregorian::date> Calendar::createDateArrayForRecurrentTask(Task* task, int numOfDays, boost::gregorian::date d1)
{
    /*
    *  create an array of recurrent dates
    */
    int freq = task->getFreq();
    vector<boost::gregorian::date> dates;

    boost::gregorian::date_duration f(freq);


    for (int j = 0; j < numOfDays; j += 8)
    {
        dates[j] = d1 + f;
        //cout << dates[j] << endl;

    }
    return dates;
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
