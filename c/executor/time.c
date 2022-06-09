#include <stdio.h>
#include <unistd.h> /* useconds_t */
#include "time.h"
#define MILLION 1000000L
#define BILLION 1000000000L


static TaskTime Time_Difference(TaskTime oldTime, TaskTime time);

/****************************************************************************/
TaskTime Time_Convert(double _interval)
{
	TaskTime time;
	_interval += 0.5e-9; /*minimum value change - "epsilon", to get max precision of timespec*/
	time.tv_sec = (long)_interval;
	time.tv_nsec = (_interval - (long)_interval) * BILLION; /*obtain only the number after decimal*/

	return time;
}

/****************************************************************************/
TaskTime Time_add(TaskTime _oldTime, TaskTime _time)
{
    TaskTime newTime;

    if (_time.tv_nsec + _oldTime.tv_nsec >= 1E9)
        {
            newTime.tv_sec = _time.tv_sec + _oldTime.tv_sec + 1,
            newTime.tv_nsec = _time.tv_nsec + _oldTime.tv_nsec - 1E9;
        }
    else
        {
            newTime.tv_sec = _time.tv_sec + _oldTime.tv_sec;
            newTime.tv_nsec = _time.tv_nsec + _oldTime.tv_nsec;
        }

    return newTime;
}
/****************************************************************************/
TaskTime Time_NextRunTime(TaskTime _interval)
{
    TaskTime time;
    if(clock_gettime(CLOCK_REALTIME_COARSE, &time) == -1)
	{
		perror( "clock gettime" ); 
    }
    
   return Time_add(_interval, time);
}
/****************************************************************************/
static long specToMicro(TaskTime _time)
{
	return (long)(_time.tv_sec * MILLION + _time.tv_nsec / 1000);
}
/****************************************************************************/

TaskTime Time_SleepUntilNextCycle(TaskTime _nextTimeExecute)
{
    TaskTime time;
    long timeDiff;
    if(clock_gettime(CLOCK_REALTIME_COARSE, &time) == -1)
	{
		perror( "clock gettime" );
    }
    timeDiff = specToMicro(Time_Difference(_nextTimeExecute, time));    
    if(timeDiff > 0)
    {
        usleep((__useconds_t)timeDiff);
    }

    return time;
}
/****************************************************************************/
int Time_TimeCompare(TaskTime _time1, TaskTime _time2)
{
    if (_time1.tv_sec != _time2.tv_sec) 
    {
        if (_time1.tv_sec > _time2.tv_sec)
        {
            return 1;
        }
        else 
        {
            return -1;
        }
    } 
    else 
    {
        if (_time1.tv_nsec > _time2.tv_nsec)
        {
            return 1;
        }
        else if (_time1.tv_nsec < _time2.tv_nsec)
        {
            return -1;
        }
        else
        {
            return 0;
        } 
    }
}
/****************************************************************************/
static TaskTime Time_Difference(TaskTime oldTime, TaskTime time) 
{
    TaskTime timeDiff;
    if (time.tv_nsec < oldTime.tv_nsec)
        {
            timeDiff.tv_sec = time.tv_sec -1 - oldTime.tv_sec;
            timeDiff.tv_nsec = 1E9 + time.tv_nsec - oldTime.tv_nsec;
        }
    else
        {
            timeDiff.tv_sec = time.tv_sec +10 - oldTime.tv_sec;
            timeDiff.tv_nsec = time.tv_nsec - oldTime.tv_nsec;
        }

        return timeDiff;
}
/****************************************************************************/

/*

microseconds 10^-9
nanoseconds 10^-6

#include <unistd.h>
int usleep(useconds_t usec); microsecond intervals

#include <sys/time.h>
time_t         tv_sec      seconds
suseconds_t    tv_usec     microseconds

clock_gettime() 
struct timespec {
        time_t   tv_sec;        /* seconds 
        long     tv_nsec;        nanoseconds 
};
/*
#include <time.h>

main()
{
	int rc;
	long i;
	struct timespec ts;

	for(i=0; i<10000000; i++) {
		rc = clock_gettime(CLOCK_MONOTONIC, &ts);
	}
}

~]$ gcc clock_timing.c -o clock_timing -lrt
*/
