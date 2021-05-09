#include "system.h"
using namespace std;

/**********************************************************
 *
 * Constructor System: Class System
 *_________________________________________________________
 * This method constructs the System class and reads the data
 * from the JSON file, populating the list of tasks
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will construct the System and load all
 *     tasks into memory
 ***********************************************************/
System::System(std::map<string, Task *> &taskMap,
               std::map<string, std::map<string, vector<TimeBlock> > > &TBMap)
{
    scheduler = new Scheduler(taskMap, TBMap);
    calendar = new Calendar();
}

System::System()
{
    calendar = new Calendar();
    taskMap = calendar->readFromFile(map, "data.json");
    scheduler = new Scheduler(taskMap, map);
}

System::~System()
{
    delete scheduler;
    delete calendar;
}

/**********************************************************
 *
 * Method displayMainMenu(): Class System
 *_________________________________________________________
 * This method displays the main menu, sort of the main loop
 * of the program. From here, the user can choose to create,
 * delete, or edit a task, or see the calendar
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be created
 ***********************************************************/
void System::displayMainMenu()
{
    if (scheduler->createNewTask("Present this project", "20200511", 17.50,
        .50, 9))
    {
        cout << "We added the task" << endl;
    }
    else
    {
        cout << "Conflict" << endl;
    }
    //cout << scheduler->getTask("Intern Interview", "20200428")->getName() << endl;
    calendar->displayCalendar("20200415", 60, map);
    int userInput;
    bool exitFlag = false;
    do {
        cout << "\nWelcome to the PSS! Select from the options below:\n";
        cout << "1 - Display the calendar\n";
        cout << "2 - Add a task\n";
        cout << "3 - Delete a task\n";
        cout << "4 - Edit a task\n";
        cout << "5 - Exit\n";
        userInput = getIntUserInput();
        if (userInput == 1) {
            displayCalendar();
        }
        else if (userInput == 2) {
            displayCreateMenu();
        }
        else if (userInput == 3) {
            displayDeleteMenu();
        }
        else if (userInput == 4) {
            displayEditMenu();
        }
        else if (userInput == 5) {
            cout << "Exiting...\n";
            exitFlag = true;
        }
        else {
            cout << "Invalid input\n";
        }
    } while (exitFlag == false);
}

/**********************************************************
 *
 * Method displayCreateMenu(): Class System
 *_________________________________________________________
 * This method displays the create menu, allowing the user to
 * create a task. A task is created if the actions are not cancelled
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be created
 ***********************************************************/
void System::displayCreateMenu()
{
    cout << "Create Menu\n";

    int userInput;
    string taskType;
    string userTime;
    string userDate;
    string endDate;
    string userDuration;
    string taskName;
    bool exitFlag = false;
    bool validName = true;
    bool timeAvailable = true;
    string userFrequency;
    do {
        cout << "Select type:\n";
        cout << "1 - Transient\n";
        cout << "2 - Recurring\n";
        userInput = getIntUserInput();
        switch (userInput) {
            case 1: {
                cout << "Selecting Transient...\n";
                cout << "Enter the time (please enter a time in the format 13:45): ";
                getline(cin, userTime);

                if (userTime.length() == 1 && userTime[0] == 'q') {
                    exitFlag = true;
                }
                else if (validTimeFormat(userTime) == true) {

                    cout << "Enter the date (please enter a date in the format YYYYMMDD): ";
                    getline(cin, userDate);

                    if (userDate.length() == 1 && userDate[0] == 'q') {

                        exitFlag = true;

                    }
                    else if (validDateFormat(userDate) == true) {

                        cout << "Enter the duration in minutes: ";
                        getline(cin, userDuration);

                        if (userDuration.length() == 1 && userDuration[0] == 'q') {

                            exitFlag = true;

                        }
                        else if (validDurationFormat(userDuration) == true) {
                            
                            if(scheduler->timeValid(userDate, convertTimeStrToFloat(userTime), convertDuration(userDuration))){
                                cout << "Enter the name of the task: ";
                                getline(cin, taskName);
                                if (taskName.length() == 1 && taskName[0] == 'q') {
                                    exitFlag = true;
                                }
                                else if (scheduler->nameValid(taskName)) { //if  name is available
                                    cout << "Select the type of task: \n";
                                    cout << "1 - Visit\n2 - Shopping\n3 - Appointment\n";
                                    getline(cin, taskType);
                                    if (taskType.length() == 1 && taskType[0] == 'q') {
                                        exitFlag = true;
                                    }
                                    else if (taskType.length() == 1 && (taskType[0] == '1' || taskType[0] == '2' || taskType[0] == '3')) {

                                        //Call sheduler with these values
                                        cout << "Scheduling a task with name: " << taskName << "\nDuration: " << userDuration << "\nStart date: " << userDate << "\nTime: " << userTime << "\nType: " << stoi(taskType) << "\n";
                                        scheduler->createNewTask(taskName, userDate, convertTimeStrToFloat(userTime), convertDuration(userDuration), stoi(taskType), userDate, 1);
                                        exitFlag = true;


                                    }
                                    else {
                                        cout << "Invalid task type.\n";
                                    }
                                }
                            }
                        }
                        else if (validDurationFormat(userDuration) == false) {
                            cout << "That is not a valid duration\n";
                            break;
                        }
                        else {
                            cout << "That time is not available.\n";
                            break;
                        }
                    }
                    else {
                        cout << "Invalid input. Please type 1 or 2.\n";
                        break;
                    }
                }
                else {
                    cout << "That is not a valid time.\n";
                }
                break;
            }
            case 2: {
                cout << "Selecting Recurring...\n";
                cout << "Enter the time (please enter a time in the format 13:45): ";
                std::getline(cin, userTime);

                if (userTime.length() == 1 && userTime[0] == 'q') {
                    exitFlag = true;
                }
                else if (validTimeFormat(userTime) == true) {
                    cout << "Enter the start date (please enter a date in the format YYYYMMDD): ";

                    std::getline(cin, userDate);

                    if (userDate.length() == 1 && userDate[0] == 'q') {
                        exitFlag = true;
                    }
                    else if (validDateFormat(userDate) == true) {

                        cout << "Enter the end date (please enter a date in the format YYYYMMDD): ";

                        std::getline(cin, endDate);
                        if (endDate.length() == 1 && endDate[0] == 'q') {

                            exitFlag = true;

                        }
                        else if (validDateFormat(endDate) == true && stoi(endDate) > stoi(userDate)) {

                            cout << "Enter duration in minutes: ";

                            getline(cin, userDuration);

                            if (userDuration.length() == 1 && userDuration[0] == 'q') {

                                exitFlag = true;

                            }
                            else if (validDurationFormat(userDuration) == true) {

                                cout << "Select from the following frequencies:\n";
                                cout << "1 - Daily\n";
                                cout << "2 - Weekly\n";

                                getline(cin, userFrequency);
                                if (userFrequency.length() == 1 && userFrequency[0] == 'q') {
                                    exitFlag = true;
                                }
                                else if (userFrequency == "1" || userFrequency == "2") {

                                    //AND time and date are available

                                    if (scheduler->timeValid(userDate, convertTimeStrToFloat(userTime), convertDuration(userDuration))) { //time is available

                                        cout << "Enter the name of the task: ";
                                        getline(cin, taskName);
                                        if (taskName.length() == 1 && taskName[0] == 'q') {
                                            exitFlag = true;
                                        }
                                        else if (scheduler->nameValid(taskName)) { //scheduler.nameValid(taskName) 

                                            cout << "Select the type of task: \n";
                                            cout << "1 - Class\n2 - Study\n3 - Sleep\n4 - Exercise\n5 - Work\n6 - Meal\n";
                                            getline(cin, taskType);
                                            if (taskType.length() == 1 && taskType[0] == 'q') {
                                                exitFlag = true;
                                            }
                                            else if (taskType.length() == 1 && (taskType[0] == '1' || taskType[0] == '2' || taskType[0] == '3' || taskType[0] == '4' || taskType[0] == '5' || taskType[0] == '6')) {


                                                //Call sheduler with these values
                                                cout << "Sheduling a task with name: " << taskName << "\nDuration: " << userDuration << "\nStart date: " << userDate << "\nEnd date: " << endDate << "\nFrequency: " << userFrequency << "\nTime: " << userTime << "\n";
                                                //Call sheduler with these values
                                                scheduler->createNewTask(taskName, userDate, convertTimeStrToFloat(userTime), convertDuration(userDuration), stoi(taskType), endDate, (stoi(userFrequency) == 1 ? 1 : 7));
                                                exitFlag = true;
                                                //scheduler.createNewTask(taskName, userDate, converTime(userTime), convertDuration(userDuration), stoi(taskType), userDate, 1)


                                            }
                                            else {
                                                cout << "Invalid task type.";
                                            }
                                        }
                                        else { //name
                                            cout << "That name already exists in the system, please use a unique name.\n";
                                        }
                                    }
                                    else {
                                        cout << "That time is not available.\n";
                                        exitFlag = true;
                                        break;
                                    }
                                }
                                else { //invalid frequency

                                    cout << "That is not a valid frequency.\n";
                                    exitFlag = true;
                                    break;
                                }

                            }
                            else if (validDurationFormat(userDuration) == false) {
                                cout << "That is not a valid duration\n.";
                                break;
                            }

                        }
                        else { //invalid end date
                            cout << "Invalid end date.\n";
                            break;
                        }

                    }
                    else { //invalid start date
                        cout << "Invalid start date.\n";
                        break;
                    }
                }
                else {
                    cout << "Invalid time.\n";
                }
                break;
            }
            default: {
                cout << "Invalid input.\n";
                break;
            }
        }
    } while (exitFlag == false);
}

/**********************************************************
 *
 * Method displayEditMenu(): Class System
 *_________________________________________________________
 * This method displays the edit menu, allowing the user to
 * edit a task. A task is edited if the actions are not cancelled
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be created
 ***********************************************************/
void System::displayEditMenu()
{
    
    cout << scheduler->timeValid("20200511", 17.50, 0.50) << endl;
    cout << "--Edit Menu--\n";
    //cout << scheduler->deleteTask("Present this project") << endl;
    /*Task* taskToEdit = scheduler->getTask("Present this project", "20200511");
    cout << scheduler->nameValid("Present this projct") << endl;
    if (scheduler->deleteTask(taskToEdit->getName())) {
        if (scheduler->createNewTask("COW", taskToEdit->getStartDateString(), taskToEdit->getStartTime(), taskToEdit->getDuration(), taskToEdit->getTypeInt())) {
            cout << "Successfully changed name.\n";
        }
        else {
            scheduler->createNewTask(taskToEdit->getName(), taskToEdit->getStartDateString(), taskToEdit->getStartTime(), taskToEdit->getDuration(), taskToEdit->getTypeInt());
            cout << "Unable to make edit.\n";
        }
    }
    else {
        cout << "Unable to make change.\n";
    }*/

    string taskName;
    string taskDate;
    string userInput;
    bool validInput = false;

    //Get info for what task the user want's to edit
    do {
        //Select task name
        validInput = false;
        do {
            cout << "What is the name of the task you want to edit? (q to exit) ";
            getline(cin, userInput);
            
            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (!scheduler->nameValid(userInput))//If task exists with that name
            {
                taskName = userInput;
                validInput = true;
            }
            else
            {
                cout << "No task exists by that name.\n";
            }
        } while (!validInput);

        //Select task date
        validInput = false;
        do {
            cout << "Enter the date of the task (YYYYMMDD): ";
            getline(cin, userInput);

            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (validDateFormat(userInput))//If valid date format
            {
                taskDate = userInput;
                validInput = true;
            }
            else
            {
                cout << "Invalid date format.\n";
            }
        } while (!validInput);
    } while (!validInput);

    //Get task from scheduler
    Task* editTask = scheduler->getTask(taskName, taskDate);

    //If the task could not be found exit
    if (editTask == nullptr) {
        cout << "Couldn't retrieve task from scheduler.\n";
        return;
    }

    cout << endl;
    editTask->display();    //Display task information

    //Make edit choice
    validInput = false;
    char editChoice;
    do {
        cout << "\nPlease select what you want to edit: \n";
        cout << "1 - Name\n";
        cout << "2 - Date\n";
        cout << "3 - Start Time\n";
        cout << "4 - Duration";
        cout << ((editTask->isRecurrent()) ? "\n5 - Frequency\n" : "\n");
        cout << "0 - Exit\n>";

        getline(cin, userInput);
        //Check for exit command
        if (userInput.length() == 1 && (userInput[0] == 'q' || userInput[0] == '0')) {
            return;
        }

        if (userInput.length() != 1)    //user must enter one character
        {
            cout << "Invalid choice, too long.\n";
            continue;
        }
        
        //Verify input is valid. Feel free to replace with better logic, my if wasn't working for some reason so I did this
        switch (userInput[0]) {
        case 'q':
        case '0':
            return;
        case '5':
            if (!(editTask->isRecurrent()))
            {
                cout << "Invalid choice, 5 is too large.\n";
                continue;
            }
        case '1':
        case '2':
        case '3':
        case '4':
            cout << "Input recognized.\n";
            editChoice = userInput[0];
            validInput = true;
            break;
        default:
            cout << "Input not recognized.\n";
            continue;
        }
    } while (!validInput);

    //Get old data
    string tName = editTask->getName();
    string tDate = editTask->getStartDateString();
    double tStartTime = editTask->getStartTime();
    double tDuration = editTask->getDuration();
    int tType = editTask->getTypeInt();
    string tEndDate = "";   //TODO: How to get these values from a recurrent task
    int tFreq = 1;

    switch (editChoice)
    {
    case '1':
        //Edit name
        validInput = false;
        do {
            cout << "Please enter the new name? (q to exit) ";
            getline(cin, userInput);

            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (!scheduler->nameValid(userInput))//If task exists with that name
            {
                cout << "A task already exists with that name.\n";
            }
            else
            {
                tName = userInput;
                validInput = true;
            }
        } while (!validInput);
        break;
    case '2':
        //Edit date
        validInput = false;
        do {
            cout << "Enter the date of the task (YYYYMMDD): ";
            getline(cin, userInput);

            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (validDateFormat(userInput))//If valid date format
            {
                if (scheduler->timeValid(userInput, tStartTime, tDuration)) //Check if time is available
                {
                    taskDate = userInput;
                    validInput = true;
                }
                else
                {
                    cout << "Date creates conflict.\n";
                }
            }
            else
            {
                cout << "Invalid date format.\n";
            }
        } while (!validInput);
        break;
    case '3':
        //Edit start time
        validInput = false;
        do {
            cout << "Please enter the new start time (Format: 13:45): ";
            userInput = "";
            getline(cin, userInput);

            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (validTimeFormat(userInput)) {
                if (scheduler->timeValid(tDate, convertTimeStrToFloat(userInput), tDuration))
                {
                    tStartTime = convertTimeStrToFloat(userInput);
                    validInput = true;
                }
                else
                {
                    cout << "Time creates conflict.\n";
                }
            }
            else {
                cout << "Invalid time format.\n";
            }
        } while (!validInput);
        break;
    case '4':
        //Edit duration
        validInput = false;
        do {
            cout << "Please enter the new duration in minutes (i.e. 90 for 1 hour and 30 minutes): ";
            getline(cin, userInput);

            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (validDurationFormat(userInput)) {   //Input is valid
                if (scheduler->timeValid(tDate, tStartTime, convertDuration(userInput)))//New duration doesn't create time conflict
                {
                    tDuration = convertDuration(userInput);
                    validInput = true;
                }
                else
                {
                    cout << "Duration creates conflict.\n";
                }
            }
            else {
                cout << "Invalid duration.\n";
            }
        } while (!validInput);

        break;
    case '5':
        //Edit frequency
        validInput = false;
        do {
            cout << "Please enter the new frequency: ";
            userInput = getIntUserInput();
            int freq = stoi(userInput);

            if(freq > 0){
                tFreq = freq;
                validInput = true;
            }
            else{
                cout <<"Invalid frequency.\n";
            }
        } while (!validInput);
        break;
    }

    if (scheduler->deleteTask(editTask->getName())) {
        if (scheduler->createNewTask(tName, tDate, tStartTime, tDuration, tType)) {
            cout << "Successfully modified task.\n";
        }
        else {
            scheduler->createNewTask(editTask->getName(), editTask->getStartDateString(), editTask->getStartTime(), editTask->getDuration(), editTask->getTypeInt());
            cout << "Unable to insert new task.\n";
        }
    }
    else {
        cout << "Unable to delete old task.\n";
    }
}

/**********************************************************
 *
 * Method displayDeleteMenu(): Class System
 *_________________________________________________________
 * This method displays the delete menu, allowing the user to
 * delete a task. A task is deleted if the actions are not cancelled
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing but a task may be deleted
 ***********************************************************/
void System::displayDeleteMenu()
{
    //boolean values used for testing
    bool taskExists = true;
    bool validName = true;

    bool exitFlag = false;

    string taskName;
    string userDate;
    string userInput;
    bool validInput = false;

    //Select task
    do {
        //Select task name
        validInput = false;
        do {
            cout << "What is the name of the task you want to edit? (q to exit) ";
            getline(cin, userInput);

            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (!scheduler->nameValid(userInput))//If task exists with that name
            {
                taskName = userInput;
                validInput = true;
            }
            else
            {
                cout << "No task exists by that name.\n";
            }
        } while (!validInput);

        //Select task date
        validInput = false;
        do {
            cout << "Enter the date of the task (YYYYMMDD): ";
            getline(cin, userInput);

            if (userInput.length() == 1 && userInput[0] == 'q') {
                return;
            }

            if (validDateFormat(userInput))//If valid date format
            {
                userDate = userInput;
                validInput = true;
            }
            else
            {
                cout << "Invalid date format.\n";
            }
        } while (!validInput);
    } while (!validInput);

    //Get task
    Task* deleteTask = scheduler->getTask(taskName, userDate);

    if (deleteTask == nullptr) {
        cout << "Couldn't retrieve task from scheduler.\n";
        return;
    }

    cout << endl;
    deleteTask->display();    //Display task information

    
    string userTime;
    string userDuration;

    if (deleteTask->isTransient()) {
        //delete task

        if (scheduler->deleteTask(taskName)){
            cout << "Deleting transient with the name " << taskName << "\n";
        }else{
            cout << "Could not delete transient task.";
        }
    }
    else if (deleteTask->isRecurrent()) {
        cout << "Would you like to delete all of the reccurring tasks or just one instance?\n";
        cout << "1 - One Instance (create anti-task)\n";
        cout << "2 - All instances of this task\n";
        getline(cin, userInput);
        if (userInput.length() == 1 && userInput[0] == 'q') {
            return;
        }
        else if (userInput[0] == '1') {
            cout << "Enter the tasks start date: ";
            getline(cin, userDate);
            if (userDate.length() == 1 && userDate[0] == 'q') {
                return;
            }
            else if (validDateFormat(userDate)) {
                cout << "Enter the tasks time: ";
                getline(cin, userTime);
                if (userTime.length() == 1 && userTime[0] == 'q') {
                    return;
                }
                else if (validTimeFormat(userTime)) {

                    cout << "Enter the tasks duration: ";
                    getline(cin, userDuration);
                    if (userDuration.length() == 1 && userDuration[0] == 'q') {
                        return;
                    }
                    else if (validDurationFormat(userDuration)) {
                        cout << "Creating an anti-task with a duration of" << userDuration << ", time " << userTime << ", and name " << taskName << "\n";

                    }
                    else {
                        cout << "Duration is not valid.";
                    }

                }
                else {
                    cout << "Time is not valid.";
                }

            }
            else {
                cout << "Date is not valid.";
            }


        }
        else if (userInput[0] == '2') {

            //find task
            //delete task;
            if (scheduler->deleteTask(taskName)){
                cout << "Deleting recuring tasks with the name " << taskName << "\n";
            }else{
                cout << "Could not delete.";
            }

        }
    }
    else {
        cout << "Error: task is neither recurrent or transient.";
    }
}

/**********************************************************
 *
 * Method displayCalendar(): Class System
 *_________________________________________________________
 * This method displays the calendar, allowing the user to
 * see his/her tasks laid out
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void System::displayCalendar()
{
    cout << "Calendar Menu\n";
    bool exitFlag = false;

    string date = "";
    do {
        cout << "Please enter the date you want to view the calendar from (YYYYMMDD format, 'q' to exit): ";
        std::getline(cin, date);

        if (date.length() == 1 && date[0] == 'q') {//If user want's to exit
            cout << "Exiting...\n";
            return;
        }
        else if (stringIsNumber(date) && validDateFormat(date) == true) {//If date is correctly formatted then allow exit
            exitFlag = true;
        }
        else {
            continue;
        }
    } while (exitFlag == false);

    int duration = 0;
    do {
        cout << "Please enter how many days of the calendar you want to view in numbers (-1 to exit): ";
        string temp = "";
        std::getline(cin, temp);
        duration = stringToInt(temp);

        if (temp.length() == 1 && temp[0] == 'q') {//If user want's to exit
            cout << "Exiting...\n";
            return;
        }
        else if (duration != -1 && duration >= 1) {//If date is correctly formatted then allow exit
            cout << "Valid duration\n";
            exitFlag = true;
        }
        else if (duration < 1){
            cout << "Invalid duration.\n";
        }
        else {
            continue;
        }
    } while (exitFlag == false);
    
    calendar->displayCalendar(date, duration, scheduler->getTBMap());
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
bool System::validDurationFormat(string userDuration) { //finished
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
bool System::validDateFormat(string userDate) {
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
float System::convertDuration(string userDuration) {
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
bool System::validTimeFormat(string userTime) {
    if (userTime.length() != 5 || userTime[2] != ':')
        return false;

    string hours = userTime.substr(0, 2);
    string minutes = userTime.substr(3, 5);

    if (!stringIsNumber(hours) || !stringIsNumber(minutes))
        return false;

    return true;
}

/**********************************************************
 *
 * Method convertTimeStrToFloat(): Class Menu
 *_________________________________________________________
 * This method turns user time strings into floats
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 * POST-CONDITIONS
 *     This returns the float version of the string.
 ***********************************************************/
double System::convertTimeStrToFloat(string userTime) {
    if (!validTimeFormat(userTime))
        return NULL;

    string hours = userTime.substr(0, 2);
    string minutes = userTime.substr(3, 5);
    int intHours = stoi(hours);
    int intMins = stoi(minutes);
    double time = static_cast<double>(intHours + (intMins / 60));
    
    return time;
}

/**********************************************************
 *
 * Method stringIsNumber(): Class Menu
 *_________________________________________________________
 * This method checks if a string is capable of stoi'ing to an int.
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 * POST-CONDITIONS
 *     This returns true if string is a number.
 ***********************************************************/
bool System::stringIsNumber(string in)
{
    for (char c : in)
        if (!isdigit(c))
            return false;
    return true;
}

/**********************************************************
 *
 * Method stringToInt(): Class Menu
 *_________________________________________________________
 * This method attempts to return the int version of a string.
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 * POST-CONDITIONS
 *     This returns the int version of in or -1 if it failed.
 ***********************************************************/
int System::stringToInt(const string in)
{
    if (in.length() > 0 && stringIsNumber(in))
        return stoi(in);
    else
        return -1;
}

/**********************************************************
 *
 * Method getIntUserInput(): Class Menu
 *_________________________________________________________
 * This method attempts get an int input from the user safely.
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 * POST-CONDITIONS
 *     This returns the int version of in or -1 if it failed.
 ***********************************************************/
int System::getIntUserInput()
{
    string temp = "";
    std::getline(cin, temp);
    return stringToInt(temp);
}