#ifndef RECURRENTTASK_H
#define RECURRENTTASK_H

#include "task.h"

class RecurrentTask : public Task
{
public:
    enum R_Type
    {
        Class = 1, Study, Sleep, Exercise, Work, Meal
    };
    enum Frequency { Daily = 1, Weekly = 7};


    RecurrentTask(const string& new_name, const string& new_startDate,
        double new_startTime, int new_duration, const string& newEndDate,
        Frequency f, R_Type type):Task(new_name, new_startDate, new_startTime,
            new_duration), endDate(newEndDate), f(f), task_type(type){}

    void set_type(R_Type new_type);


    //~RecurrentTask() override;

private:
    R_Type task_type = Class;
    string endDate;

    // default daily
    Frequency f = Daily;

};
#endif // RECURRENTTASK_H
