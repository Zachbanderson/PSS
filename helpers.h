#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <string>
#include "task.h"
#include "timeblock.h"

using namespace std;
vector<TimeBlock> createTimeBlocks(Task *task);
bool addTaskToTimeBlockMap(Task* task,     //Task that the TimeBlock points to
                    date date,      //Date that the task happens
                    std::map<string, std::map<string, vector<TimeBlock>>>
                    &TimeBlockMap);  //Map that stores all the times of the tasks
int convertTypeToInt(string type);
void printValid(std::map<string, std::map<string, vector<TimeBlock>>> &TimeBlockMap);
bool validDateFormat(string userDate);
bool validDurationFormat(string userDuration);
float convertDuration(string userDuration);
bool validTimeFormat(string userTime);

#endif // HELPERS_H
