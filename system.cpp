#include "system.h"

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
}

System::~System()
{
    delete scheduler;
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
    cout << "Edit Menu\n";
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
    cout << "Delete Menu\n";
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
        else if (duration != -123 && duration >= 1) {//If date is correctly formatted then allow exit
            cout << "Valid duration\n";
            exitFlag = true;
        }
        else if (duration < 1){
            cout << "Duration must be greater than 1.\n";
        }
        else {
            continue;
        }
    } while (exitFlag == false);
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
 *     This returns the int version of in or -123 if it failed.
 ***********************************************************/
int System::stringToInt(const string in)
{
    if (in.length() > 0 && stringIsNumber(in))
        return stoi(in);
    else
        return -123;
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