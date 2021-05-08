#include "helpers.h"

/**********************************************************
 *
 * Method createTimeBlocks(): Helper function
 *_________________________________________________________
 * This function creates a vector of 96 TimeBlocks
 *_________________________________________________________
 * PRE-CONDITIONS
 *     task(Task*)-Task to point the TimeBlocks to
 *
 * POST-CONDITIONS
 *     This function returns a vector of 96 TimeBlocks
 ***********************************************************/
vector<TimeBlock> createTimeBlocks(Task *task)
{
    //Check type of task
    float increment = 0.25;
    double taskStartTime = task->getStartTime();
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
            TimeBlock tb(nullptr, timeBlockStartTime);
            tbVector.push_back(tb);
            timeBlockStartTime += increment;
        }

    }

    return tbVector;
}

/**********************************************************
 *
 * Method addTaskToTimeBlockMap(): Helper function
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
//Reformat this later to not return true or false. No validation should be done here
bool addTaskToTimeBlockMap(Task* task,     //Task that the TimeBlock points to
                    date date,      //Date that the task happens
                    std::map<string, std::map<string, vector<TimeBlock>>>
                    &TimeBlockMap)  //Map that stores all the times of the tasks
{
    string taskYear = boost::lexical_cast<string>(date.year());
    string taskDay = boost::lexical_cast<string>(date.day_of_year());

    //If we haven't found a task with this year yet
    if(TimeBlockMap.find(taskYear) == TimeBlockMap.end())
    {
        //cout << "Haven't found the year" << endl;
        //Inserting a blank map at the year mark
        TimeBlockMap.insert(std::pair<string, std::map<string,
                            vector<TimeBlock>>>(taskYear, std::map<string,
                                                vector<TimeBlock>>()));
//        cout << "Inserted " << taskYear << endl;
//        cout << "Inserted " << taskDay << " at " << taskYear << endl;
        //Creating a vector of 96 empty TimeBlocks at the day of the year
        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
                                         (taskDay, createTimeBlocks(task)));
        //cout << "Added the TimeBlocks" << endl;

    }
    //If the year is in the map but the day isn't
    else if(TimeBlockMap.at(taskYear).find(taskDay) == TimeBlockMap.at(taskYear).end())
    {
        //cout << "Haven't found the day" << endl;
        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
                                         (taskDay, createTimeBlocks(task)));
//        cout << "Inserted " << taskDay << " at " << taskYear << endl;
//        cout << "Added the TimeBlocks" << endl;
    }

    //Trying to add a task on a day where there is already a scheduled task
    //This is the only time where the function may return false
    else
    {
        //Checking the TimeBlocks to see if any are occupied
        for(float i = 0; i < task->getDuration(); i += .25)
        {
            if(TimeBlockMap.at(taskYear).at(taskDay).at
                    (((task->getStartTime() + i) / .25)).get_task() != nullptr
                    && TimeBlockMap.at(taskYear).at(taskDay).
                    at(((task->getStartTime() + i) / .25)).get_task()->getType()
                    != "Cancellation")
            {
                return false;
            }
        }
        for(float i = 0; i < task->getDuration(); i += .25)
        {
            //This line accesses the TimeBlock at the correct place. Doesn't
            //need to search through the vector
            TimeBlockMap.at(taskYear).at(taskDay).at
                    (((task->getStartTime() + i) / .25)).set_task(task);
        }

    }

    //Returning true means that the task was added
    return true;
}

/**********************************************************
 *
 * Method convertTypeToInt(): Helper function
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
int convertTypeToInt(string type)
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

/**********************************************************
 *
 * Method printValid(): Helper function
 *_________________________________________________________
 * This function prints the map that checks if a task is valid
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function prints the years and days that are in the valid map
 ***********************************************************/
void printValid(std::map<string, std::map<string, vector<TimeBlock>>> &TimeBlockMap)
{
    for(std::map<string, std::map<string, vector<TimeBlock>>>::iterator
        it = TimeBlockMap.begin(); it != TimeBlockMap.end(); it++)
    {
        //Printing out the year and the days that tasks happen in that year
        cout << it->first << ": ";
        cout << it->second.begin()->first;
        std::map<string, TimeBlock>::iterator it2;
        for(std::map<string, vector<TimeBlock>>::iterator it2 =
            std::next(it->second.begin()); it2 != it->second.end(); it2++)
        {
            cout << ", " << it2->first;
        }
        cout << endl;
    }
}

/**********************************************************
 *
 * Method validDurationFormat(): Class Menu
 *_________________________________________________________
 * This method checks if the duration is an integer and is a multiple of 15
 *_________________________________________________________
 * PRE-CONDITIONS
 *     userDuration(string) - The string version of duration
 * POST-CONDITIONS
 *     This returns true if the duration is valid
 ***********************************************************/
bool validDurationFormat(string userDuration) { //finished
    int duration;
    for (int i = 0; i < userDuration.length(); i++) {
        if (isdigit(userDuration[i]) == false) {
            return false;
        }
    }
    duration = stoi(userDuration);
    if (duration % 15 == 0 && duration > 0 && duration / 15 <= 96) {
        return true;
    }
    cout << "Duration must be a multiple of 15.\n";
    return false;
}

/**********************************************************
 *
 * Method validDateFormat(): Helper function for Menu
 *_________________________________________________________
 * This method checks if the date is in a valid format.
 *_________________________________________________________
 * PRE-CONDITIONS
 *     userDate(string) - The date in iso format
 * POST-CONDITIONS
 *     This returns true if the date is in a valid format.
 ***********************************************************/
bool validDateFormat(string userDate) {
    if (userDate.length() != 8) {
        cout << "Date must be in the format YYYYMMDD.\n";
        return false;
    }

    string strYear = "";
    string strMonth = "";
    string strDay = "";

    //Extract y, m, d iteratively
    for (int i = 0; i < 4; i++) {
        if (isdigit(userDate[i]) == false) {
            cout << "Non digit in year.\n";
            return false;
        }
        else {
            strYear += userDate[i];
        }
    }
    for (int i = 4; i < 6; i++) {
        if (isdigit(userDate[i]) == false) {
            cout << "Non digit in month.\n";
            return false;
        }
        else {
            strMonth += userDate[i];
        }
    }
    for (int i = 6; i < 8; i++) {
        if (isdigit(userDate[i]) == false) {
            cout << "Non digit in day.\n";
            return false;
        }
        else {
            strDay += userDate[i];
        }
    }

    //Convert to integers
    int year = stoi(strYear);
    int month = stoi(strMonth);
    int day = stoi(strDay);

    //Check that month and day are within bounds
    if (month >= 1 && month <= 12 && day >= 1) {
        switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day <= 31) {
                return true;
            }
            else {
                cout << "Too many days for month " << month << endl;
            }
            break;
        case 2:
            if (day <= 28) {
                return true;
            }
            else {
                cout << "Too many days for month " << month << endl;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day <= 30) {
                return true;
            }
            else {
                cout << "Too many days for month " << month << endl;
            }
            break;
        }
    }
    else {
        cout << "Month must be 01-12 and day must be >= 1.\n";
    }
    cout << "Date must be in the format YYYYMMDD.\n";
    return false;
}

/**********************************************************
 *
 * Method convertDuration(): Class Menu
 *_________________________________________________________
 * This method converts a valid duration into a float. I.e 15 = 0.25
 *_________________________________________________________
 * PRE-CONDITIONS
 *     Valid duration format
 * POST-CONDITIONS
 *     This returns the duration represent as a float
 ***********************************************************/
float convertDuration(string userDuration) {
    float newDuration;
    float oldDuration = stof(userDuration);

    newDuration = oldDuration / 60;
    return newDuration;

}

/**********************************************************
 *
 * Method validTimeFormat(): Class Menu
 *_________________________________________________________
 * This method checks if the time is in a valid format.
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 * POST-CONDITIONS
 *     This returns true if the time is in a valid format.
 ***********************************************************/
bool validTimeFormat(string userTime) {
    string strHour = "";
    string strMinute = "";
    //int minute = -1;
    int minute = -1;
    int hour = 0;
    if (userTime.length() == 7) {
        if (isdigit(userTime[0]) && isdigit(userTime[2]) && isdigit(userTime[3])) {
            strHour += userTime[0];
            strMinute += userTime[2];
            strMinute += userTime[3];
            minute = stoi(strMinute);
            hour = stoi(strHour);
            //return true;
            if (hour > 0 && hour < 10 && minute > -1 && minute < 60) {

                if (userTime[5] == 'p' || userTime[5] == 'P' || userTime[5] == 'a' || userTime[5] == 'A') {
                    return true;
                }
            }
        }
        else if (userTime.length() == 8) {
            if (isdigit(userTime[0]) && isdigit(userTime[1]) && isdigit(userTime[3]) && isdigit(userTime[4])) {
                strHour += userTime[0];
                strHour + userTime[1];
                strMinute += userTime[3];
                strMinute += userTime[4];
                if (hour > 0 && hour < 10 && minute > -1 && minute < 60) {
                    if (userTime[5] == 'p' || userTime[5] == 'P' || userTime[5] == 'a' || userTime[5] == 'A') {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}