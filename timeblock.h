#ifndef TIMEBLOCK_H
#define TIMEBLOCK_H

#include "task.h"

class TimeBlock
{

public:
    TimeBlock() {}
    TimeBlock(Task* newTask, float newStartTime) :task(newTask), tb_startTime(newStartTime){}

    float get_tb_startTime();
    void set_task(Task* taskPtr);
    Task* get_task();


    ~TimeBlock();
private:
    Task* task;
    float tb_startTime;
    //float increment = 0.25;
};

#endif // TIMEBLOCK_H
