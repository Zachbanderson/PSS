#include "timeblock.h"


double TimeBlock::tbGetStartTime()
{
    return tbStartTime;
}
void TimeBlock::setTask(Task* taskPtr)
{
    task = taskPtr;
}

Task* TimeBlock::getTask()
{
    return task;
}
TimeBlock::~TimeBlock()
{
    task = nullptr;
}
