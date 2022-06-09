#include <stdio.h>


int main(void)
{
	int *ptr;
	int str1 = 0;
	struct students
	{
		char name[10];
		int age;
		long id;
		int edu;
	};
	
	struct students str[5] =
	{
		{"Dan", 21, 245, 16},
		{"Michal", 32, 287, 12},
		{"Efrat", 28, 163, 16},
		{"Johny", 26, 24, 12},
		{"Rotem", 340, 197, 14}
	
	};
	struct *ptr = &str;
	str = *ptr;
	printf("%p \n", str1);
	/*printf("Student name: %s\nAge: %d\nID: %ld\nEDU: %d\n", str1.name,str1.age,str1.id,str1.edu);*/
	
}
