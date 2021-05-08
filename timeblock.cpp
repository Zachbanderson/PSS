#include "timeblock.h"

/**********************************************************
 *
 * Method tbGetStartTime(): Class TransientTask
 *_________________________________________________________
 * This method returns the strat time of the task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     return
 ***********************************************************/
double TimeBlock::tbGetStartTime()
{
    return tbStartTime;
}

/**********************************************************
 *
 * Method setTask(Task* taskPtr): Class TransientTask
 *_________________________________________________________
 * This method sets a new task
 *_________________________________________________________
 * PRE-CONDITIONS
 *     sets the task to the new task
 *
 * POST-CONDITIONS
 *     none
 ***********************************************************/
void TimeBlock::setTask(Task* taskPtr)
{
    task = taskPtr;
}

/**********************************************************
 *
 * Method getTask(): Class TransientTask
 *_________________________________________________________
 * This method returns the task associated
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     return the new task associated witht he timeBlock
 ***********************************************************/

Task* TimeBlock::getTask()
{
    return task;
}
TimeBlock::~TimeBlock()
{
    task = nullptr;
}
