#include <stdio.h>
#include <stdlib.h>

typedef struct Person
{
	int m_id;
	char m_name[30];
	int m_age;
}Person;

int main()
{
	Person persons[] = {{1111111,"blabla",30},{2222222,"blabla",30},{3333333,"bvaf",30},{5555555,"blabla",30},{6666666,"blabla",30}}; 
	int i;
	Person newPerson[5];
	char fileName[] = "person.bin";
	FILE *file;
	if((file = fopen(fileName , "w+")) == NULL)
	{
		printf("File could not be opened \n");
		return;
	}
	fwrite(persons,sizeof(Person),5,file);
	fseek(file,0,SEEK_SET);
	fread(newPerson,sizeof(Person),5,file);
	for(i = 0; i < 5; i++)
	{
		printf("%d %s %d\n", newPerson[i].m_id, newPerson[i].m_name, newPerson[i].m_age);
	}
	fseek(file,0,SEEK_SET);
	fclose(file);
}

