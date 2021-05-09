#include <utility>

#include "includes.h"
#include "json.hpp"
#include "scheduler.h"


using namespace std;
using nlohmann::json;


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


void printTask(TimeBlock* tb_array, int tb_array_size)
{
    cout << "Task Name: " << tb_array[0].getTask()->getName() << endl;
    //cout << "Type of the task is: " << tb_array[0].getTask()->get_type() << endl;
    cout << "This task has: " << tb_array_size
        << " time blocks starting from ";

    for (int i = 0; i < tb_array_size; i++)
    {
        cout << tb_array[i].tbGetStartTime() << " ";

    }
    cout << endl;

}

int main()
{

    //Testing reading/writing JSON
    {
        cout << "Starting" << endl;
        Calendar calendar;
        //cout << "Created calendar" << endl;
        std::map<string, std::map<string, vector<TimeBlock>>> map;
        std::map<string, Task*> taskMap = calendar.readFromFile(map, "data.json");
        //cout << "Read tasks" << endl;
        //printValid(map);

        Scheduler scheduler(taskMap, map);

        calendar.displayCalendar("20200415", 7, map);


        if(scheduler.createNewTask("Present this project", "20200511", 17.50,
                                   .50, 9))
        {
            cout << "We added the task" << endl;
        }
        else
        {
            cout << "Conflict" << endl;
        }

        calendar.displayCalendar("20200415", 60, map);

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
        //		cout << tb_date_pair.second[j].getStartTime() << " ";
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
