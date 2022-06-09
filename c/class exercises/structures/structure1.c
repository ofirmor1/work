#include <stdio.h>

struct students
{
	char name[10];
	int age;
	long id;
	int edu;
};

int main(void)
{

	
	struct students str1 =  {"ofir", 30, 123456789, 16};
	printf("Student name: %s\nAge: %d\nID: %ld\nEDU: %d\n", str1.name,str1.age,str1.id,str1.edu);
	
}
