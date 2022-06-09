#ifndef __TIME_H__
#define __TIME_H__
#include <time.h> /* timespec */

/****************************************************************************/
typedef struct timespec TaskTime; /*time in nanosec*/
/****************************************************************************/

/**
 * @brief function to convert to time to timespec measures
 * 
 * @param _interval the period of recurrence of task
 * @return TaskTime - time in timespec struct.
 */
TaskTime Time_Convert(double _interval);
/****************************************************************************/

/**
 * @brief update the time of a task
 * 
 * @param _oldTime the time of the last occurance of a task
 * @param _time - time to be added.
 * @return TaskTime new time of a task
 */
TaskTime Time_add(TaskTime _oldTime, TaskTime _time);
/****************************************************************************/

/**
 * @brief fuction to calculate the next time a task should be exec.
 * 
 * @param _intervalis the period of recurrence of task
 * @return TaskTime time to Re exec a task
 */
TaskTime Time_NextRunTime(TaskTime _interval);
/****************************************************************************/

/**
 * @brief function to sleep a task until next cycle.
 * 
 * @param _nextTimeExecute - next time a task should be exec
 * @return TaskTime time
 */
TaskTime Time_SleepUntilNextCycle(TaskTime _nextTimeExecute);
/****************************************************************************/

/**
 * @brief function to compare times
 * 
 * @param _time1 - time of task to compare
 * @param _time2 - time of task to compare
 * @return int 
 * 1 if _time1 > _time2
 * 0 if _time1 < _time2
 * -1 otherwise
 */
int Time_TimeCompare(TaskTime _time1, TaskTime _time2);


#endif /*#ifndef __TIME_H__*/
