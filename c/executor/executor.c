#include <time.h>
#include <stdio.h>
#include "executor.h"
#include "task.h"
#include "time.h"
#include "/home/ofir/EXPERIS/DS/genericHeap.h"
#define MAGIC_NUMBER 59826

struct PeriodicExecutor
{
    Heap* m_tasks;
    Vector* m_vec;
    int m_pause;
    int m_magicNumber;
};

static void PeriodicExecutor_InitialTasksRunTime(Vector* _vec);
static void ExecTasks(PeriodicExecutor* _executor);

/****************************************************************************/
PeriodicExecutor* PeriodicExecutor_Create(const char* _name,
clockid_t _clk_id)
{
    PeriodicExecutor* executor;
    executor = (PeriodicExecutor*)malloc(sizeof(PeriodicExecutor));
    if(NULL == executor)
    {
        return NULL;
    }
    executor->m_vec = VectorCreate(6,2);
	if (NULL == executor->m_vec)
	{
		free(executor);
		return NULL;
	}
    executor->m_tasks = Heap_Build(executor->m_vec, Task_Compare);
    if(NULL == executor->m_tasks)
    {
        VectorDestroy(&executor->m_vec,NULL);
        free(executor);
        return NULL;
    }
    executor->m_pause = 0;
    executor->m_magicNumber = MAGIC_NUMBER;

    return executor;
}
/****************************************************************************/
void PeriodicExecutor_Destroy(PeriodicExecutor* _executor)
{
    if(NULL == _executor || _executor->m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
    if(_executor->m_tasks != NULL)
    {
        Heap_Destroy(&_executor->m_tasks);
    }
    if(_executor->m_vec != NULL)
    {
        VectorDestroy(&_executor->m_vec, Task_Destroy);
    }
	_executor->m_magicNumber = 0;
	free(_executor);
}
/****************************************************************************/
ExecutorErr PeriodicExecutor_Add(PeriodicExecutor* _executor, int (*_taskFunction)(void *), void* _context, size_t _period_ms)                                                                                                                                                                                                                                                              
{
    Task* task;
    if(NULL == _executor || NULL == _taskFunction)
    {
        return EXECUTOR_NOT_INITIALIZED;
    }
    task = Task_Create(_taskFunction,_context, _period_ms);
    if(NULL == task)
    {
        return EXECUTOR_ALLOCATION_FAILED;
    }
    if(Heap_Insert((_executor->m_tasks), task) != HEAP_SUCCESS)
    {
        Task_Destroy(task);
        return EXECUTOR_ALLOCATION_FAILED;
    }
    return EXECUTOR_SUCCESS;
}
/****************************************************************************/
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor)
{
    if(NULL == _executor)
    {
        return 0;
    }
    PeriodicExecutor_InitialTasksRunTime(_executor->m_vec);
    while(Heap_Size(_executor->m_tasks) > 0 && _executor->m_pause == 0)
    {
        ExecTasks(_executor);
    }

    return Heap_Size(_executor->m_tasks);
}
/****************************************************************************/
static void ExecTasks(PeriodicExecutor* _executor)
{
    Task* task =(Task*)Heap_Extract(_executor->m_tasks);
    if(NULL == task)
    {
        return;
    }
    if(Task_Run(task) == 0) /*success*/
    {
        if(Heap_Insert(_executor->m_tasks,task) != HEAP_SUCCESS)
        {
            Task_Destroy(task);
        }
    }
    else
    {
        Task_Destroy(task);
    }
}
/****************************************************************************/
static void PeriodicExecutor_InitialTasksRunTime(Vector* _vec)
{
    struct timespec curTime;
    clock_gettime(CLOCK_REALTIME_COARSE, &curTime);
    VectorForEach(_vec,Task_Initial_Next_Run_Time,(void*)&curTime);
}
/****************************************************************************/
ExecutorErr PeriodicExecutor_Pause(PeriodicExecutor* _executor)
{
    if(NULL == _executor)
    {
        return EXECUTOR_NOT_INITIALIZED;
    }
    _executor->m_pause = 1;

    return EXECUTOR_SUCCESS;
}
