#include <stdexcept>
#include "boost/date_time.hpp"
#include "calendar.h"

using namespace std;


Calendar::Calendar()
{

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

    ofstream outfile(fname);
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

