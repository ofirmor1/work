#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <stdlib.h>
#include <time.h>

/**
 * @brief task executor to manage all tasks
 * 
 */

typedef struct PeriodicExecutor PeriodicExecutor;
typedef int (*taskFunc)(void* _context);

typedef enum
{
    EXECUTOR_SUCCESS = 0,
    EXECUTOR_ALLOCATION_FAILED,
    EXECUTOR_NOT_INITIALIZED
}ExecutorErr;

/**
 * @brief Create a periodic executor that will measure time using given clock.
Clockid_t specify the id of the system clock to be used. CLOCK_REALTIME,
CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC and similar provided it’s
supported by the underlying system.
 * @param _name - name of executor
 * @param _clk_id - the id of the system clock to be used.
 * @return PeriodicExecutor* 
 */

PeriodicExecutor* PeriodicExecutor_Create(const char* _name,
clockid_t _clk_id);

/**
 * @brief Destroy previously created executor. Cleaning all allocated memory and resources.
 * @param _executor  - Executor
 * @return - None 
 */

void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);

/**
 * @brief Adding task to the executor
 * @param _executor  - Executor
 * @param _taskFunction is represented by a user provided function pointer. The task is called with
_context as the only parameter ,  return 0 - success, otherwise - failed
 * @param _context - user _context to provide user function.
 * @param _period_ms is the period of recurrence in milliseconds.
 * @attention check null of _taskFunction and _period_ms
 * @return ExecutorStatus: 
 *  EXECUTOR_SUCCESS = success addind a task
    EXECUTOR_ALLOCATION_FAILED - allocation faild error
    EXECUTOR_NOT_INITIALIZED - uninitialized error
 */

ExecutorErr PeriodicExecutor_Add(PeriodicExecutor* _executor, int (*_taskFunction)(void *), void* _context, size_t _period_ms);

/**
 * @brief Start running the executor. Start running the tasks previously added to the executor or resume a previously paused
Executor.
 * @param _executor - Executor
 * @return size_t number of execution cycles (user task function calls) performed.
 */

size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);
/**
 * @brief Pause the execution of the executor. If a task is currently being executed then pause after
it has completed the current cycle.
 * @param _executor  - Executor
 * @return - size_t number of tasks remaining inside the executor.
 */
ExecutorErr PeriodicExecutor_Pause(PeriodicExecutor* _executor);


#endif /*ifndef __EXECUTOR_H__*/
