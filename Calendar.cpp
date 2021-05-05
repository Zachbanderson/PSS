#include <stdexcept>
#include "boost/date_time.hpp"
#include "Calendar.h"

using namespace std;
//TO-DO: Load from JSON file into memory
//TO-DO: Make function addTask (diff function for transient/recurrent tasks
//          to add task to the map in the JSON

Calendar::Calendar()
{

}

/**********************************************************
 *
 * Destructor ~Calendar(): Class Calendar
 *_________________________________________________________
 * Destructor: deallocates all dynamically allocated memory
 * used for the taskMap
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function frees all memory. Returns nothing
 ***********************************************************/
Calendar::~Calendar()
{
    cout << "In destructor" << endl << endl;
    for(std::map<string, Task*>::iterator it = taskMap.begin();
        it != taskMap.end(); it++)
    {
        if(it->second == nullptr)
        {
            cout << "Is null pointer" << endl;
        }
        it->second->display();
        delete it->second;
    }
    cout << "We didn't crash" << endl;
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
        //TimeBlock tb(newTask1, startTime);
        //tbVector.push_back(tb);
        startTime += increment;
    }

    return tbVector; 

}

/**********************************************************
 *
 * Method writeToFile(): Class Calendar
 *_________________________________________________________
 * This method writes the tasks in JSON form to a file
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function writes the tasks to a file. Returns nothing
 ***********************************************************/
void Calendar::writeToFile()
{
    string serialized = "[";
    std::map<string, Task*>::iterator it = taskMap.begin();
    serialized += it->second->serialize();
    for(++it; it != taskMap.end(); it++)
    {
        serialized += "," + it->second->serialize();
    }
    serialized += "]";
    cout << serialized << endl;

    json written = json::parse(serialized);
    string pretty = written.dump(2);

    ofstream outfile("output.json");
    outfile << pretty;
    outfile.close();
}

/**********************************************************
 *
 * Method readFromFile(): Class Calendar
 *_________________________________________________________
 * This method reads the tasks in JSON form from a file and
 * constructs a map based on it.
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function populates the task list. Returns nothing
 ***********************************************************/
// Create map<year<date<timeblocks>>> from JSON file
void Calendar::readFromFile()
{
    ifstream infile(dataName);

    json info = json::parse(infile);

    //Searching through all of the tasks in the JSON
    for(json::iterator it = info.begin(); it != info.end(); it++)
    {
        json tempJSON = *it;
//        cout << tempJSON.dump(2) << endl;
//        cout << tempJSON.dump() << endl;
        string name = tempJSON["Name"];
        //cout << "Got name" << endl;
        string type = tempJSON["Type"];
        //cout << "Got type" << endl;
        int date;
        double startTime = tempJSON["StartTime"];
        //cout << "Got all strings" << endl;
        double duration = tempJSON["Duration"];

        //If the task has "Frequency" as a key, it's a recurring task
        if(tempJSON.find("Frequency") != tempJSON.end())
        {
            //cout << "Recurring" << endl;
            int frequency = tempJSON["Frequency"];
            date = tempJSON["StartDate"];
            int endDate = tempJSON["EndDate"];
            //cout << frequency << endl;
            //cout << endDate << endl;

            RecurrentTask* r = new RecurrentTask(name, to_string(date),
                                                 startTime, duration,
                                                 static_cast<Task::TaskTypes>
                                                 (convertTypeToInt(type)),
                                                 to_string(endDate),
                            static_cast<RecurrentTask::Frequency>(frequency));
            taskMap.insert(std::pair<string, Task*>(name, r));
            //r->display();
            //r = nullptr;

        }
        else
        {
            //cout << "Transient" << endl;
            date = tempJSON["Date"];
            TransientTask* t = new TransientTask(name, to_string(date),
                                                 startTime, duration,
                                                 static_cast<Task::TaskTypes>
                                                 (convertTypeToInt(type)));
            taskMap.insert(std::pair<string, Task*>(name, t));
            //t->display();
            //t = nullptr;
        }
    }

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

void Calendar::printTasks()
{
    for(std::map<string, Task*>::iterator it = taskMap.begin();
        it != taskMap.end(); it++)
    {
        it->second->display();
    }
}

/**********************************************************
 *
 * Method convertTypeToInt(): class Calendar
 *_________________________________________________________
 * This function messily converts the type to the correct enum
 * in the task class. Not scalable but workable for our purposes.
 *_________________________________________________________
 * PRE-CONDITIONS
 *     type(string) - Task type
 *
 * POST-CONDITIONS
 *     This function returns the enum number associated with the task
 ***********************************************************/
int Calendar::convertTypeToInt(string type)
{
    if(type == "Cancellation")
        return 0;
    else if(type == "Class")
        return 1;
    else if(type == "Study")
        return 2;
    else if(type == "Sleep")
        return 3;
    else if(type == "Exercise")
        return 4;
    else if(type == "Work")
        return 5;
    else if(type == "Meal")
        return 6;
    else if(type == "Visit")
        return 7;
    else if(type == "Shopping")
        return 8;
    else if(type == "Appointment")
        return 9;
    else
        return -1;
}
