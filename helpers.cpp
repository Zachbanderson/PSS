#include "helpers.h"

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
            TimeBlock tb(nullptr, taskStartTime);
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
bool addTaskToTimeBlockMap(Task* task,     //Task that the TimeBlock points to
                    date date,      //Date that the task happens
                    std::map<string, std::map<string, vector<TimeBlock>>>
                    &TimeBlockMap)  //Map that stores all the times of the tasks
{
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

//    //printValid(TimeBlockMap);


//    //Returning false means that the task wasn't added
//    return false;
    string taskYear = boost::lexical_cast<string>(date.year());
    string taskDay = boost::lexical_cast<string>(date.day_of_year());

    //If we haven't found a task with this year yet
    if(TimeBlockMap.find(taskYear) == TimeBlockMap.end())
    {
        cout << "Haven't found the year" << endl;
        //Inserting a blank map at the year mark
        TimeBlockMap.insert(std::pair<string, std::map<string,
                            vector<TimeBlock>>>(taskYear, std::map<string,
                                                vector<TimeBlock>>()));
        cout << "Inserted " << taskYear << endl;
        cout << "Inserted " << taskDay << " at " << taskYear << endl;
        //Creating a vector of 96 empty TimeBlocks at the day of the year
        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
                                         (taskDay, createTimeBlocks(task)));
        cout << "Added the TimeBlocks" << endl;

    }
    //If the year is in the map but the day isn't
    else if(TimeBlockMap.at(taskYear).find(taskDay) == TimeBlockMap.at(taskYear).end())
    {
        cout << "Haven't found the day" << endl;
        TimeBlockMap.at(taskYear).insert(std::pair<string, vector<TimeBlock>>
                                         (taskDay, createTimeBlocks(task)));
        cout << "Inserted " << taskDay << " at " << taskYear << endl;
        cout << "Added the TimeBlocks" << endl;
    }

    //Call function to populate TimeBlocks here. Have the function return true
    //if it can be added. False otherwise
    //cout << task->getStartTime() << endl;



    ///validMap.at(taskYear).at(taskDay).populate(start, end);


    //Returning false means that the task wasn't added
    return false;
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
