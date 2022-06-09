#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "time.h"
#include "executor.h"
#include "../DS/genericHeap.h"
#include "../DS/genericVec.h"

typedef int (*userFunc)(void* _context);

int Func1(void* _context)
{
	printf("%s\n", "function 1");
	(*(int*)_context)--;
	return (*(int*)_context > 0) ? 0 : 1;
}

int Func2(void* _context)
{
	static int b = 2;
	printf("%s\n", "function 2");
	b--;
	return b ? 0 : 1;
}

int Func3(void* _context)
{
	static int c = 2;
	printf("%s\n", "function 3");
	c--;
	return c ? 0 : 1;
}

int Func4(void* _context)
{
	static int d = 2;
	printf("%s\n", "function 4");
	d--;
	return d ? 0 : 1;
}

int Func5(void* _context)
{
	static int d = 1;
	d--;
	return d ? 0 : 1;
}

int AddTask(void* _context)
{
	printf("%s\n", "Add task 'function 2'");
	PeriodicExecutor_Add((PeriodicExecutor*)_context, Func3, NULL, 4);
	return 1;
}

int PauseTasks(void* _context)
{
	printf("%s\n", "Pause all tasks");
	PeriodicExecutor_Pause((PeriodicExecutor*)_context);
	return 1;
}

/**************************Periodic Executor Create TESTS**************************/
void CreateExecWorks()
{
	PeriodicExecutor* executor = NULL;
	executor = 	PeriodicExecutor_Create("EXEC", CLOCK_REALTIME_COARSE);
	if(executor != NULL)
	{
		printf("%35.35s - %s\n","CreateExecCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","CreateExecCheck","Fail");
	}
}
/**************************Periodic Executor Destroy TESTS**************************/
void DestroyCheck()
{
	PeriodicExecutor* executor = NULL;
	executor = 	PeriodicExecutor_Create("EXEC", CLOCK_REALTIME_COARSE);
	/*PeriodicExecutor_Add(executor, Func2, NULL, 2);*/
	PeriodicExecutor_Destroy(executor);
	if(executor)
	{
		printf("%35.35s - %s\n","DestroyExecCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","DestroyExecCheck","Fail");
	}
}
/****************************************************************************/
void DoubleDestroyCheck()
{
	PeriodicExecutor* executor = NULL;
	executor = PeriodicExecutor_Create("EXEC", CLOCK_REALTIME_COARSE);
	PeriodicExecutor_Add(executor, Func2, NULL, 2);
	PeriodicExecutor_Destroy(executor);
	PeriodicExecutor_Destroy(executor);
	if(executor)
	{
		printf("%35.35s - %s\n","DoubleDestroyCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","DoubleDestroyCheck","Fail");
	}
}
/****************************************************************************/
void TasksDestroyCheck()
{
	PeriodicExecutor* executor = NULL;
	executor = PeriodicExecutor_Create("EXEC", CLOCK_REALTIME_COARSE);
	PeriodicExecutor_Add(executor, Func2, NULL, 2);
	PeriodicExecutor_Add(executor, Func4, NULL, 7);
	PeriodicExecutor_Destroy(executor);
	if(executor)
	{
		printf("%35.35s - %s\n","TasksDestroyCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","TasksDestroyCheck","Fail");
	}
}
/**************************Periodic Executor Adding Task TESTS**************************/

void AddingTaskChecks()
{
	PeriodicExecutor* executor = NULL;
	executor = PeriodicExecutor_Create("EXEC", CLOCK_REALTIME_COARSE);
	if(PeriodicExecutor_Add(executor, Func2, NULL, 2) == EXECUTOR_SUCCESS)
	{
		printf("%35.35s - %s\n","SuccessAddingTaskCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","SuccessAddingTaskCheck","Fail");
	}
	if(PeriodicExecutor_Add(NULL, Func2, NULL, 2) == EXECUTOR_NOT_INITIALIZED)
	{
		printf("%35.35s - %s\n","AddingTaskExecutorNullCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","AddingTaskExecutorNullCheck","Fail");
	}
	if(PeriodicExecutor_Add(executor, NULL, NULL, 2) == EXECUTOR_NOT_INITIALIZED)
	{
		printf("%35.35s - %s\n","AddingTaskFunctionNullCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","AddingTaskFunctionNullCheck","Fail");
	}

	PeriodicExecutor_Destroy(executor);
}

/**************************Periodic Executor Run TESTS**************************/

void ExecutorRunChecks()
{
	PeriodicExecutor* executor = NULL;
	executor = PeriodicExecutor_Create("EXEC", CLOCK_REALTIME_COARSE);
	PeriodicExecutor_Add(executor, Func5, NULL, 3);
	/*PeriodicExecutor_Add(executor, Func4, NULL, 7);*/
	if(PeriodicExecutor_Run(NULL) == 0)
	{
		printf("%35.35s - %s\n","ExecutorNullCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","ExecutorNullCheck","Fail");
	}
	/*
	if(PeriodicExecutor_Run(executor) == 1)
	{
		printf("%35.35s - %s\n","ExecutorRunSuccedCheck","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","ExecutorRunSuccedCheck","Fail");
	}
*/

	PeriodicExecutor_Destroy(executor);

}
/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/
/**************************Function TESTS**************************/
void FunctionTests()
{
	int temp = 2;
	PeriodicExecutor* executor = PeriodicExecutor_Create("EXEC", CLOCK_REALTIME_COARSE);
	if(executor != NULL)
	{
		printf("Number of tasks to execute = %ld\n", PeriodicExecutor_Run(executor));
		PeriodicExecutor_Add(executor, Func1, &temp, 2.1);
/*PeriodicExecutor_Add(executor, PauseTasks, NULL, 13);*/
		PeriodicExecutor_Add(executor, Func2, NULL, 3);
		PeriodicExecutor_Add(executor, Func4, NULL, 5);
		PeriodicExecutor_Add(executor, Func3, NULL, 4);
		PeriodicExecutor_Add(executor, AddTask, NULL, 1);
		
		
	
		printf("Number of tasks to execute = %ld\n", PeriodicExecutor_Run(executor));
		PeriodicExecutor_Destroy(executor);
	}
	
}

int main()
{
	printf("/**************************Periodic Executor Create TESTS**************************/\n");
	CreateExecWorks();
	printf("/**************************Periodic Executor Destroy TESTS**************************/\n");
	DestroyCheck();
	DoubleDestroyCheck();
	TasksDestroyCheck();
	printf("/**************************Periodic Executor ADD TESTS**************************/\n");
	AddingTaskChecks();
	printf("/**************************Periodic Executor RUN TESTS**************************/\n");
	ExecutorRunChecks();
	printf("/************************************Function TESTS******************************/\n");
	FunctionTests();

	
}

/**********************test time************************/
/*
TaskTime time;
	int i;
	double tc;
	for(i = 0; i < 10; i++) 
	{
		clock_gettime(CLOCK_REALTIME_COARSE, &time);
		printf("%ld.%ld\n", time.tv_nsec/1000,time.tv_sec/1000000);
		usleep(1000000);/*in microsec
	}

	time.tv_sec = time.tv_sec;
	time.tv_nsec = time.tv_nsec * 1000;
	printf("elapsed: %d.%09ld\n", (int)time.tv_sec, (long)time.tv_nsec);
*/
