#include <utility>

#include "includes.h"
#include "json.hpp"
#include "scheduler.h"


using namespace std;
using nlohmann::json;

void testJSON(string fname)
{
    ifstream infile(fname);
    json js = json::parse(infile);

    cout << js.dump(2) << endl;

    //Extracts each task from the json task lists
    //In this for loop, the *it returns the task information in braces
    for(json::iterator it = js.begin(); it != js.end(); it++)
    {
        json temp = *it;
        cout << temp.dump(2) << endl;
        cout << "Name: " << temp["Name"] << endl;
    }

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
//void writeToFile(std::map<string, Task*> taskMap)
//{
//    string serialized = "[";
//    std::map<string, Task*>::iterator it = taskMap.begin();
//    serialized += it->second->serialize();
//    for(++it; it != taskMap.end(); it++)
//    {
//        serialized += "," + it->second->serialize();
//    }
//    serialized += "]";
//    cout << serialized << endl;

//    json written = json::parse(serialized);
//    string pretty = written.dump(2);

//    ofstream outfile("output.json");
//    outfile << pretty;
//    outfile.close();
//}

//bool addTaskToValid(Task* task,     //Task that the TimeBlock points to
//                    date date,      //Date that the task happens
//                    std::map<string, std::map<string, vector<TimeBlock>>>
//                    &TimeBlockMap); //Map that stores all the times of the tasks
//int convertTypeToInt(string type);
//void printValid(std::map<string, std::map<string, vector<TimeBlock>>> &TimeBlockMap);
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
//std::map<string, Task*> readFromFile(std::map<string, std::map<string, vector<TimeBlock>>> &map)
//{
//    ifstream infile("data.json");
//    std::map<string, Task*> taskMap;

//    json info = json::parse(infile);

//    //Searching through all of the tasks in the JSON
//    for(json::iterator it = info.begin(); it != info.end(); it++)
//    {
//        json tempJSON = *it;

////        cout << tempJSON.dump(2) << endl;
////        cout << tempJSON.dump() << endl;
//        string name = tempJSON["Name"];
//        //cout << "Got name" << endl;
//        string type = tempJSON["Type"];
//        //cout << "Got type" << endl;
//        int date;
//        double startTime = tempJSON["StartTime"];
//        //cout << "Got all strings" << endl;
//        double duration = tempJSON["Duration"];

//        //If the task has "Frequency" as a key, it's a recurring task
//        if(tempJSON.find("Frequency") != tempJSON.end())
//        {
//            //cout << "Recurring" << endl;
//            int frequency = tempJSON["Frequency"];
//            date = tempJSON["StartDate"];
//            int endDate = tempJSON["EndDate"];
//            //cout << frequency << endl;
//            //cout << endDate << endl;

//            RecurrentTask* r = new RecurrentTask(name, to_string(date),
//                                                 startTime, duration,
//                                                 static_cast<Task::TaskTypes>
//                                                 (convertTypeToInt(type)),
//                                                 to_string(endDate),
//                            static_cast<RecurrentTask::Frequency>(frequency));
//            taskMap.insert(std::pair<string, Task*>(name, r));

////            cout << "Start date is:" << r->getStartDate() << endl;
////            cout << "End date is:" << r->getEndDate() << endl;

//            //Looping through all the dates in the recurring task and adding
//            //them to the validity map
//            for(boost::gregorian::date d = r->getStartDate();
//                d <= r->getEndDate(); d = d + date_duration(frequency))
//            {
//                //cout << "Date is: " << d << endl;
//                addTaskToValid(r, d, map);
//            }

//        }
//        else
//        {
//            //cout << "Transient" << endl;
//            date = tempJSON["Date"];
//            TransientTask* t = new TransientTask(name, to_string(date),
//                                                 startTime, duration,
//                                                 static_cast<Task::TaskTypes>
//                                                 (convertTypeToInt(type)));
//            taskMap.insert(std::pair<string, Task*>(name, t));
//            addTaskToValid(t, t->getStartDate(), map);
//        }
//    }
//    cout << "Printing valid map" << endl;
//    printValid(map);
//    return taskMap;
//}

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
//bool addTaskToValid(Task* task,     //Task that the TimeBlock points to
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
//    cout << date << endl;
//    ///validMap.at(taskYear).at(taskDay).populate(start, end);


//    //Returning false means that the task wasn't added
//    return false;
//}

/**********************************************************
 *
 * Method printTasks(): class Calendar
 *_________________________________________________________
 * This function prints all tasks in the calendar
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function prints all the tasks in the taskMap
 ***********************************************************/
void printTasks(std::map<string, Task*> taskMap)
{
    for(std::map<string, Task*>::iterator it = taskMap.begin();
        it != taskMap.end(); it++)
    {
        it->second->display();
    }
}

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
//void printValid(std::map<string, std::map<string, vector<TimeBlock>>> &TimeBlockMap)
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
//int convertTypeToInt(string type)
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



void printTask(TimeBlock* tb_array, int tb_array_size)
{
    cout << "Task Name: " << tb_array[0].get_task()->getName() << endl;
    //cout << "Type of the task is: " << tb_array[0].get_task()->get_type() << endl;
    cout << "This task has: " << tb_array_size
        << " time blocks starting from ";

    for (int i = 0; i < tb_array_size; i++)
    {
        cout << tb_array[i].get_tb_startTime() << " ";

    }
    cout << endl;

}

int main()
{

    //Testing reading/writing JSON
    {
        cout << "Starting" << endl;
        Calendar calendar;
        cout << "Created calendar" << endl;
        std::map<string, std::map<string, vector<TimeBlock>>> map;
        std::map<string, Task*> taskMap = calendar.readFromFile(map, "data.json");
        cout << "Read tasks" << endl;

        Scheduler scheduler(taskMap, map);

        TransientTask newTask("Get drunk", "20210923", 21.00, 2,
                              TransientTask::TaskTypes(9));
        if(scheduler.addTTask(newTask))
        {
            cout << "We added the task" << endl;
        }
        else
        {
            cout << "Conflict" << endl;
        }
        taskMap = scheduler.getTaskMap();

        calendar.writeToFile(taskMap, "stored.json");

        return 0;
    }
    {
        // testing timeblock

        //1- get information from user
        string new_name = "Create a prototype for PSS";
        string new_startDate = "20210419";
        float new_startTime = 4.00;
        int new_duration = 2;

        //2- check if time and name are available


        //3- create task
        Task* newTask1 = new TransientTask(new_name, new_startDate,
            new_startTime, new_duration, TransientTask::Visit);

        //newTask1->set_type(TransientTask::Shopping);

        // 4- create a timeBlock
        double increment = 0;
        int tb_array_size = static_cast<int>(new_duration / 0.25);
        const int tb_array_capacity = 96;
        TimeBlock tb_array[tb_array_capacity];

        for (int i = 0; i <= tb_array_size; i++)
        {
            float start_time = new_startTime + increment;
            TimeBlock tb(newTask1, start_time);
            increment += 0.25;
            tb_array[i] = tb;

        }
        // save to database

        printTask(tb_array, tb_array_size);

    }
    {

        //3- create a recurrent task

        //a- get information from user
        string new_name = "Create a prototype for PSS";
        string new_startDate = "20210419";
        double new_startTime = 4.00;
        int freq = 7;

        cout << "Enter task duration:  ";
        int new_duration = 0;
        cin >> new_duration;

        //b- check if time and name are available

        std::string newEndDate = "20210430";

        Task* newTask2 = new RecurrentTask(new_name, new_startDate,
            new_startTime, new_duration, Task::Exercise, newEndDate, RecurrentTask::Weekly);

        // now type can be included in the constructor
        //newTask2->set_type(RecurrentTask::Exercise);

        // c- get the time lapse between start time and end time...

        // Converting ISO Format (YYYYMMDD) String to date object
        boost::gregorian::date d1 = boost::gregorian::date_from_iso_string(new_startDate);
        boost::gregorian::date d2 = boost::gregorian::date_from_iso_string(newEndDate);

        boost::gregorian::date_duration day_range = d2 - d1;
        // cast the number of days ( duration of dates format) to integer
        int numb_of_days = day_range.days();

         cout << d2 <<" - " <<d1 << " = "<< numb_of_days << endl;

        // d- create a timeBlock
        float increment = 0;
        int tb_array_size = static_cast<int>(new_duration / 0.25);

        /*
        *  create an array of timeBlocks
        */
        TimeBlock* tb_array = new TimeBlock[tb_array_size];
        for (int i = 0; i <= tb_array_size; i++)
        {

            TimeBlock tb(newTask2, new_startTime + increment);
            increment += 0.25;
            tb_array[i] = tb;
        }


        /*
        *  create an array of recurrent dates
        */
        boost::gregorian::date* dates = new boost::gregorian::date[numb_of_days];

        cout << dates[0] << endl;
        boost::gregorian::date_duration f(freq);
        //int n = numb_of_days / freq;


        for (int j = 0; j < numb_of_days; j+=8)
        {
            dates[j] = d1 + f;
            cout << dates[j] << endl;

        }



        //pair<boost::gregorian::date*, TimeBlock*> tb_date_pair;
        //
        //tb_date_pair =  make_pair(dates, tb_array) ;
        //
        //for (int i = 0; i < n; i++)
        //{
        //	cout << tb_date_pair.first[i] << "  ";
        //
        //	for (int j = 0; j < tb_array_size; j++)
        //	{
        //		cout << tb_date_pair.second[j].get_tb_startTime() << " ";
        //	}
        //	cout << endl;
        //}


        delete [] tb_array;
        tb_array = nullptr;

        delete [] dates;
        dates = nullptr;


    }

    //{
    //	using namespace boost::gregorian;
    //
    //		// Converting ISO Format (YYYYMMDD) String to date object
    //	date d1 = date_from_iso_string("20160221");
    //	cout << d1 << endl;
    //}


    cout << endl;
    system("pause");
    return 0;

}
