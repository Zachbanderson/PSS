#include "includes.h"
#include "json.hpp"

#include <utility>

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
void printTask(TimeBlock* tb_array, int tb_array_size)
{
    cout << "Task Name: " << tb_array[0].get_task()->get_name() << endl;
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

    testJSON("tasks.json");

    return 0;
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
        float new_startTime = 4.00;
        int freq = 7;

        cout << "Enter task duration:  ";
        int new_duration = 0;
        cin >> new_duration;

        //b- check if time and name are available

        std::string newEndDate = "20210430";

        Task* newTask2 = new RecurrentTask(new_name, new_startDate,
            new_startTime, new_duration, newEndDate, RecurrentTask::Weekly, RecurrentTask::Exercise);

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
