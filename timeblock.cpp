#include "timeblock.h"


float TimeBlock::get_tb_startTime()
{
    return tb_startTime;
}
void TimeBlock::set_task(Task* taskPtr)
{
    task = taskPtr;
}

Task* TimeBlock::get_task()
{
    return task;
}
TimeBlock::~TimeBlock()
{
    task = nullptr;
}
