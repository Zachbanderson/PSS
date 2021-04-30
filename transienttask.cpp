#include "transienttask.h"


void TransientTask::set_type(T_Type new_type)
{
    task_type = new_type;
}

int TransientTask::get_type()
{
    return task_type;
}
