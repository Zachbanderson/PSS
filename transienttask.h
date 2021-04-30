#ifndef TRANSIENTTASK_H
#define TRANSIENTTASK_H

#include "task.h"

class TransientTask : public Task
{
public:
    enum T_Type
    {
        Visit = 7, Shopping, Appointment,
    };

    TransientTask(const string& new_name, const string& new_startDate,
        double new_startTime, int new_duration, T_Type type):
        Task(new_name, new_startDate,
        new_startTime, new_duration), task_type(type) {}

    void set_type(T_Type new_type);
    int get_type();


    //~TransientTask(){}

private:
    T_Type task_type = Appointment;

};

#endif // TRANSIENTTASK_H
