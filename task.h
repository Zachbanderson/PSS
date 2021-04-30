#ifndef TASK_H
#define TASK_H

#include <string>
#include <variant>

using namespace std;

class Task
{

public:
    enum R_Type
    {
        Class = 1, Study, Sleep, Exercise, Work, Meal
    };


    // this default constructor is only for testing task types
    //Task() {}

    Task(const string& new_name, const string& new_startDate,
        double new_startTime, double new_duration)
        :name(new_name), startDate(new_startDate),
        startTime(new_startTime), duration(new_duration) {}

    //virtual void set_type(int new_type);

    //virtual int get_type();
    double get_duration();
    string get_name();



    //virtual ~Task() {}

private:
    // startDate format: YYYYMMDD
    string name, startDate;
    double startTime, duration;
    int task_type;
};

#endif // TASK_H
