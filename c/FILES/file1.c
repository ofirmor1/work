#include <stdio.h>
#include <stdlib.h>

typedef struct Person
{
int m_id; /* Primary Key */

char m_name[128];

int m_age;

}Person;

int main(void)
{
	Person p =
	{
		1111111,
		"blabla",
		30
	};
	Person newP;
	FILE *cfPtr;
	if((cfPtr = fopen("persons.txt" , "w+")) == NULL)
	{
		printf("File could not be opened \n");
	}
	else
	{
		fprintf(cfPtr, "id %d \nname %s \nage %d\n", p.m_id, p.m_name, p.m_age);
		
		fclose(cfPtr);
	}
	
	if((cfPtr = fopen("persons.txt", "r")) == NULL)
	{
		printf("File could not be opened \n");
	}
	else
	{
		fscanf(cfPtr, "id %d \nname %s \nage %d\n", &newP.m_id, newP.m_name, &newP.m_age);
		printf("id %d \nname %s \nage %d\n", newP.m_id, newP.m_name, newP.m_age);
		fclose(cfPtr);
	}
	
}
