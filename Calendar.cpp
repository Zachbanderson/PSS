#include <stdexcept>
#include "boost/date_time.hpp"
#include "calendar.h"
#include "helpers.h"

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
void Calendar::writeToFile(std::map<string, Task*> taskMap, string fname, date start, date end)
{
    string serialized = "[";
    std::map<string, Task*>::iterator it = taskMap.begin();
    serialized += it->second->serialize();
    for(++it; it != taskMap.end(); it++)
    {
        if(it->second->getStartDate() >= start && it->second->getStartDate() <= end)
        //cout << "Name of the task is " << it->second->getName() << endl;
            serialized += "," + it->second->serialize();
        else if(it->second->getStartDate() > end)
            break;
    }
    serialized += "]";
    //cout << serialized << endl;

    json written = json::parse(serialized);
    string pretty = written.dump(2);

    ofstream outfile(fname);
    outfile << pretty;
    outfile.close();
}

/**********************************************************
 *
 * Method displayCalendar(): Class Calendar
 *_________________________________________________________
 * This method displays the calendar, allowing the user to
 * see his/her tasks laid out
 *_________________________________________________________
 * PRE-CONDITIONS
 *     date(string) - startDate of the time period user wants to see
 *     rangeOfDays(int) - rangeOfDays of time user wants to see, in days
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Calendar::displayCalendar(string date, int rangeOfDays, std::map<string,
                                                std::map<string,
                                                 vector<TimeBlock>>>
                                                 &TBMap)
{
  try 
  {
    boost::gregorian::date d = boost::gregorian::date_from_iso_string(date);  // Create date from '20210507' format 
    string taskYear = boost::lexical_cast<string>(d.year());                  // Store year from date in a string ('2021')
    string taskMon = boost::lexical_cast<string>(d.month());                  // Store month from date in a string ('5')
    string taskDay = boost::lexical_cast<string>(d.day_of_year());            // Store day number out of whole year ('20210507' -> '126')
    string displayDate = boost::lexical_cast<string>(d.day());                // Store day from date ('20210507' -> '7')
    string dayOfWeek = boost::lexical_cast<string>(d.day_of_week());          // Store day of the week ('20210507' -> 'Friday')

    boost::gregorian::date_period dp(d, days(rangeOfDays + 1));                  // The rangeOfDays of dates we're displaying
    
    // Find task in timeBlockMap from date 
    if(rangeOfDays != 0)
    {
      string startDate = boost::lexical_cast<string>(dp.begin());             // Beginning date from rangeOfDays ('2021-05-07' format)
      string endDate = boost::lexical_cast<string>(dp.last());                // End date from rangeOfDays ('2021-05-14' format)

      // Use the calendar to get the last day of the month
      boost::gregorian::date d1 = date_from_iso_string(date);                 // Create date from '20210507' format
      boost::gregorian::date d2 = from_simple_string(endDate);                // Create date from '2021-05-14' format
      string d1Start = boost::lexical_cast<string>(d1.day_of_week());         // Day of the week ('20210507' -> 'Friday')
      string d2End = boost::lexical_cast<string>(d2.day_of_week());           // Day of the week ('20210507' -> 'Friday')

      if(rangeOfDays == 1) 
      {
        string startDate = boost::lexical_cast<string>(dp.begin());
        cout << "----------------------------------------------------------------------------" << endl;
        cout << setw(30) << dayOfWeek << ", " << startDate << endl;
        cout << "----------------------------------------------------------------------------" << endl;
      }
      else
      {
        cout << "----------------------------------------------------------------------------" << endl;
        cout << setw(23) << d1Start << ", " << startDate << " to " << d2End << ", " << endDate << endl;
        cout << "----------------------------------------------------------------------------" << endl;
      }
      // using namespace boost::gregorian;
     
      // Construct an iterator starting with the start date
      boost::gregorian::day_iterator ditr(d1);
      // Loop through the days and print each one
      for (; ditr <= d2; ++ditr) 
      {
        cout << ditr->day_of_week() << ": " << to_simple_string(*ditr) << endl;
        cout << "--------------------" << endl;
        if(rangeOfDays == 1)
        {
          ++ditr;                                                             // To make sure only one date is printed
        }
        //Year is in time block map
        if(TBMap.find(taskYear) != TBMap.end())
        {
          // Date is in Year in time block map
            string day = boost::lexical_cast<string>(ditr->day_of_year());
            //cout << "Day is: " << day << endl;
            if(TBMap.at(taskYear).find(day) != TBMap.at(taskYear).end())
            {
              // Read the tasks from the time blocks for the whole day (24 * rangeOfDays)
              for(int i = 0; i < 96; i++)
              {
                // Checking to see if any time blocks are occupied with a task ===This is what im unsure about===
                if(TBMap.at(taskYear).at(day).at(i).getTask() != nullptr
                  && TBMap.at(taskYear).at(day).at(i).getTask()->getType()
                  != "Cancellation")
                {
                  // Print Task to Console
                  string taskName = TBMap.at(taskYear).at(day).at(i).getTask()->getName();
                  double taskStartTime = TBMap.at(taskYear).at(day).at(i).getTask()->getStartTime();
                  double taskDuration = TBMap.at(taskYear).at(day).at(i).getTask()->getDuration();
                  double taskEndTime = taskStartTime + taskDuration;
                  string taskStartTimeString = TBMap.at(taskYear).at(day).at(i).getTask()->getStartTimeString();
                  string taskEndTimeString = convertDoubleToString(taskEndTime);
                  cout << taskStartTimeString << " to " << taskEndTimeString << ": " << taskName << endl;
                  i += taskDuration / .25;
                }
              }

            }
        }
        else 
        {
          cout << "No tasks scheduled." << endl;
        }
        cout << "--------------------" << endl;
      }
    } 
  }
  catch(exception& e) 
  {
    cout << "Error bad date, check your entry: \n" << "  Details: " << e.what() << endl;
  }  
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
    //printValid(TBMap);
    return taskMap;
}

string Calendar::convertDoubleToString(double time)
{
  int hours = static_cast<int>(time);
  int minutes = static_cast<int>(time * 100) % 100;
  string strMins;
  switch(minutes)
  {
    case 25:
      strMins = "15";
      break;
    case 50:
      strMins = "30";
      break;
    case 75:
      strMins = "45";
      break;
    default:
      strMins = "00";
      break;
  }
  
  string convertedTime;
  if (hours >= 13)                 // If time is 1:00 pm or more
  {
    hours = 0;
    convertedTime = to_string(hours) + ":" + strMins + " PM";
  }
  else if (hours == 12)           // If time is noon
  {
    convertedTime = to_string(hours) + ":" + strMins + " PM";
  }
  else if (hours == 0)            // If time is midnight
  {
    hours = 12;
    convertedTime = convertedTime = to_string(hours) + ":" + strMins + " AM";
  }
  else                            // Time is AM
  {
    convertedTime = to_string(hours) + ":" + strMins + " AM";
  }

  return convertedTime;
}
