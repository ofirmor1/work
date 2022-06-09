#include <stdio.h>
#include <string.h>
#define ERROR 0
#define SUCCESS 1

typedef struct 
{
	char name[10];
	int age;
	long id;
	int edu;
	int sizeOfStructArray;
}student;

int sortingStruct (student *ptr,int sizeOfStructArray)
{
	int compare;
	int i,swapped = 1;
	if(ptr==NULL)
	{
		return ERROR;
	}

	while (swapped)
	{
		swapped = 0;
		for(i=0;i<sizeOfStructArray-1;i++)
		{
			if(strcmp(ptr[i].name,ptr[i+1].name) > 0)
			{	
				swap(ptr, i, i+1);
				swapped = 1;
			}
		}
		sizeOfStructArray--;
	}
	return SUCCESS;	
}

int swap(student *ptr,int i, int j)
{
	student temp;
	temp = ptr[i];
	ptr[i] = ptr[j];
	ptr[j] = temp;
}

int main (void)
{
	int i;
	int sizeOfStructArray;
	student s1;
	student arryStudent[5]={{"a",20,123,3},{"e",30,1153,5},
	{"d",40,354,10},{"b",30,1153,5},{"c",30,1153,5}};
	

	strcpy(s1.name,"shiran");
	s1.age = 31;
	s1.id = 201063922;	
	s1.edu = 17;

	
	sizeOfStructArray=sizeof(arryStudent)/sizeof (arryStudent[0]);
	sortingStruct (arryStudent , sizeOfStructArray);
	
	for(i=0; i<sizeOfStructArray;i++)
	{	
		printf("name:%s\nage:%d\nid: %ld\nedu:%d\n\n\n",arryStudent[i].name,arryStudent[i].age,arryStudent[i].id,arryStudent[i].edu);
	}
		

}




