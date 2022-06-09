#ifndef __TASK_H__
#define __TASK_H__

#include <stdlib.h>
#include<sys/types.h>
#include <time.h>
/****************************************************************************/
/**
 * @brief Create a task
 * 
 */
/****************************************************************************/
typedef struct Task Task;
/****************************************************************************/
typedef enum
{
    TASK_SUCCESS = 0,
	TASK_NOT_INITIALIZED,
	TASK_REALLOCATION_FAILED,
    TASK_DESTROY_SUCCESS

}ErrResult;
/****************************************************************************/
/**
 * @brief Create a task
 * 
 * @param _func - function to insert as task.
 * @param _context - user _context to provide user function.
 * @param _interval - interval time for user function
 * @attention check null of _func and _interval
 * @return Task* 
 * 
 */

Task* Task_Create(int (*_func)(void* _context), void* _context, double _interval);
/****************************************************************************/
/**
 * @brief Free a task and Destroy it.
 * 
 * @param _task - task to be destroyed. task == NULL if succeed.
 * @return - None
 */
void Task_Destroy(void* _task);
/****************************************************************************/
/**
 * @brief - run a task.
 * @param _task - task to run.
 * @return - integer: 0 if should be called again, any other value means task should stop
 */
int Task_Run(Task* _task);
/****************************************************************************/
/**
 * @brief Compare between two tasks.
 * 
 * @param _task1 -task to compare
 * @param _task2 -task to compare
 * @return int 0 if NULL. 1 if success
 */
int Task_Compare(const void* _task1,const void* _task2);

int Task_Initial_Next_Run_Time(void* _task, size_t _index, void* _context);


























#endif /*ifndef __TASK_H__*/
