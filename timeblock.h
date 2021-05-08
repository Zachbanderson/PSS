#ifndef TIMEBLOCK_H
#define TIMEBLOCK_H

#include "task.h"

class TimeBlock
{

public:
    TimeBlock() {}
    TimeBlock(Task* newTask, float newStartTime) :task(newTask), tbStartTime(newStartTime){}

    double tbGetStartTime();
    void setTask(Task* taskPtr);
    Task* getTask();


    ~TimeBlock();
private:
    Task* task;
    float tbStartTime;
    //float increment = 0.25;
};

#endif // TIMEBLOCK_H
