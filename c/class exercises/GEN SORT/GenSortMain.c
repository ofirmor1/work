#include <stdio.h>
#include <stdlib.h>

#define YES 1
#define NO 0
#define ARR_SIZE 10

typedef struct student
{
	char name[20];
	int id;
	int age;
	int grade;
}student;

int IsBigger(const void * _e1, const void * _e2)
{
	if(*(int*)_e1 <= *(int*)_e2)
	{
		return NO;
	}
	return YES;
}

int StudenSortById(const void * _p1, const void * _p2)
{
	if(((student*)_p1) -> id <= ((student*)_p2) -> id)
	{
		return NO;
	}
	return YES;
}

static void PrintStructStudend(struct student *students_data, int _size)
{
	int studenNum;
	if(NULL == students_data)
	{
		return;
	}
	for(studenNum = 0; studenNum < _size; studenNum++)
	{
		printf("student name: %s\nstuden id: %d\nstudent age: %d\nstudent grade: %d\n\n",students_data[studenNum].name,students_data[studenNum].id,students_data[studenNum].age,students_data[studenNum].grade);
	}
}

int main(void)
{
	int size, i;
	student stData[4] = {{"st1",3,25,87},{"st2",2,27,75},{"st3",1,19,92},{"st4",4,33,83}};
	int arr[10] = {1,5,2,7,9,11,2,8,4,6};

	size = sizeof(stData)/sizeof(stData[ARR_SIZE]);

	printf("\n");
	GenSort(stData, size, sizeof(student), StudenSortById);
	printf("\n");
	PrintStructStudend(stData, size);
	
	GenSort(arr, ARR_SIZE, sizeof(int), IsBigger);
	
	printf("\n");
	for(i; i < ARR_SIZE; i++)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n");
}
