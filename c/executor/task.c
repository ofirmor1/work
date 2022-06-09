#include "task.h"
#include "time.h"
#include <stdio.h>

typedef int(*func)(void* _context);

struct Task
{
    func m_taskFunc;
    TaskTime m_interval;
    TaskTime m_nextRunTime;
    void* m_context;
};
/****************************************************************************/
Task* Task_Create(int (*_func)(void* _context), void* _context, double _interval)
{
    Task* newTask;
    if(NULL == _func || _interval <= 0)
    {
        return NULL;    
    }
    newTask = (Task*)malloc(sizeof(Task));
    if(NULL == newTask)
    {
        return NULL;
    }
    newTask->m_taskFunc = _func;
    newTask->m_context = _context;
    newTask->m_interval = Time_Convert(_interval);
    newTask->m_nextRunTime = Time_NextRunTime(newTask->m_interval);
    

    return newTask;

    
}
/****************************************************************************/
void Task_Destroy(void* _task)
{
	if (!(Task*)_task)
	{
		free((Task*)_task);
	}
}
/****************************************************************************/
int Task_Run(Task* _task)
{
    int res;
    if(NULL == _task)
    {
        return 1;
    }
    Time_SleepUntilNextCycle(_task->m_nextRunTime);
    res = _task->m_taskFunc(_task->m_context);
    _task->m_nextRunTime = Time_NextRunTime(_task->m_interval);

    return res;

}
/****************************************************************************/
int Task_Compare(const void* _task1,const void* _task2)
{
    if(NULL == _task1 || NULL == _task2)
    {
        return 0;
    }
    if (Time_TimeCompare(((Task*)_task1)->m_nextRunTime, ((Task*)_task2)->m_nextRunTime))
    {
        return 1;
    }
}
/****************************************************************************/
int Task_Initial_Next_Run_Time(void* _task, size_t _index, void* _context)
{
    if((Task*)_task != NULL)
    {
       ((Task*)_task)->m_nextRunTime = Time_add(((Task*)_task)->m_interval, *(TaskTime*)_context);
    }

    return  1;
}
