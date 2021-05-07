#include <stdexcept>
#include "boost/date_time.hpp"
#include "calendar.h"

using namespace std;

//TO-DO: Make function addTask (diff function for transient/recurrent tasks
//          to add task to the map in the JSON

Calendar::Calendar()
{
    //readFromFile();
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
//Calendar::~Calendar()
//{
//    for(std::map<string, Task*>::iterator it = taskMap.begin();
//        it != taskMap.end(); it++)
//    {
//        if(it->second == nullptr)
//        {
//            cout << "Is null pointer" << endl;
//        }
//        delete it->second;
//    }
//}


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
void Calendar::writeToFile(std::map<string, Task*> taskMap, string fname)
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

//bool addTaskToValid(Task* task,     //Task that the TimeBlock points to
//                    date date,      //Date that the task happens
//                    std::map<string, std::map<string, vector<TimeBlock>>>
//                    &TimeBlockMap); //Map that stores all the times of the tasks
//int convertTypeToInt(string type);
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
std::map<string, Task*> Calendar::readFromFile(std::map<string,
                                               std::map<string,
                                               vector<TimeBlock>>>
                                               &TBMap, string fname)
{
    ifstream infile(fname);
    std::map<string, Task*> taskMap;

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

//            cout << "Start date is:" << r->getStartDate() << endl;
//            cout << "End date is:" << r->getEndDate() << endl;

            //Looping through all the dates in the recurring task and adding
            //them to the validity map
            for(boost::gregorian::date d = r->getStartDate();
                d <= r->getEndDate(); d = d + date_duration(frequency))
            {
                //cout << "Date is: " << d << endl;
                addTaskToTimeBlockMap(r, d, TBMap);
            }

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
            addTaskToTimeBlockMap(t, t->getStartDate(), TBMap);
        }
    }
    cout << "Printing valid map" << endl;
    printValid(TBMap);
    return taskMap;
}

/**********************************************************
 *
 * Method addTaskToValid(): Class Calendar
 *_________________________________________________________
 * This method populates TimeBlocks in the TimeBlockMap based on
 * the date it appears
 *_________________________________________________________
 * PRE-CONDITIONS
 *     date(boost::gregorian::date)-The date of the task
 *
 * POST-CONDITIONS
 *     This function populates the validity map. Returns true
 *     if the date is valid. False otherwise
 ***********************************************************/
//bool Calendar::addTaskToValid(Task* task,     //Task that the TimeBlock points to
//                    date date,      //Date that the task happens
//                    std::map<string, std::map<string, vector<TimeBlock>>>
//                    &TimeBlockMap)  //Map that stores all the times of the tasks
//{
//    string taskYear = boost::lexical_cast<string>(date.year());
//    string taskDay = boost::lexical_cast<string>(date.day_of_year());

//    //If we haven't found a task with this year yet
//    if(TimeBlockMap.find(taskYear) == TimeBlockMap.end())
//    {
//        //Inserting a blank map at the year mark
//        TimeBlockMap.insert(std::pair<string, std::map<string, vector<TimeBlock>>>
//                        (taskYear, std::map<string, vector<TimeBlock>>()));
//        //Creating a vector of 96 empty TimeBlocks at the day of the year
//        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
//                                         (taskDay, vector<TimeBlock>(96,
//                                                   TimeBlock(task, 0))));

//    }
//    //If the year is in the map but the day isn't
//    else if(TimeBlockMap.at(taskYear).find(taskDay) == TimeBlockMap.at(taskYear).end())
//    {
//        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
//                                         (taskDay, vector<TimeBlock>
//                                          (96, TimeBlock(task, 0))));
//    }

//    //Call function to populate TimeBlocks here. Have the function return true
//    //if it can be added. False otherwise
//    //cout << task->getStartTime() << endl;
//    ///validMap.at(taskYear).at(taskDay).populate(start, end);

//    printValid(TimeBlockMap);


//    //Returning false means that the task wasn't added
//    return false;
//}

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

///**********************************************************
// *
// * Method printTasks(): class Calendar
// *_________________________________________________________
// * This function prints all tasks in the calendar
// *_________________________________________________________
// * PRE-CONDITIONS
// *     none
// *
// * POST-CONDITIONS
// *     This function prints all the tasks in the taskMap
// ***********************************************************/
//void printTasks(std::map<string, Task*> taskMap)
//{
//    for(std::map<string, Task*>::iterator it = taskMap.begin();
//        it != taskMap.end(); it++)
//    {
//        it->second->display();
//    }
//}

/**********************************************************
 *
 * Method printValid(): class Calendar
 *_________________________________________________________
 * This function prints the map that checks if a task is valid
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function prints the years and days that are in the valid map
 ***********************************************************/
//void Calendar::printValid(std::map<string, std::map<string, vector<TimeBlock>>> &TimeBlockMap)
//{
//    for(std::map<string, std::map<string, vector<TimeBlock>>>::iterator
//        it = TimeBlockMap.begin(); it != TimeBlockMap.end(); it++)
//    {
//        //Printing out the year and the days that tasks happen in that year
//        cout << it->first << ": ";
//        cout << it->second.begin()->first;
//        std::map<string, TimeBlock>::iterator it2;
//        for(std::map<string, vector<TimeBlock>>::iterator it2 =
//            std::next(it->second.begin()); it2 != it->second.end(); it2++)
//        {
//            cout << ", " << it2->first;
//        }
//        cout << endl;
//    }
//}

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
//int Calendar::convertTypeToInt(string type)
//{
//    if(type == "Cancellation")
//        return 0;
//    else if(type == "Class")
//        return 1;
//    else if(type == "Study")
//        return 2;
//    else if(type == "Sleep")
//        return 3;
//    else if(type == "Exercise")
//        return 4;
//    else if(type == "Work")
//        return 5;
//    else if(type == "Meal")
//        return 6;
//    else if(type == "Visit")
//        return 7;
//    else if(type == "Shopping")
//        return 8;
//    else if(type == "Appointment")
//        return 9;
//    else
//        return -1;
//}
