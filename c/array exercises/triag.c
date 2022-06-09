#include <stdio.h>

/* 	
i count the triangular rib length
j put spaces before asterix
k put asterix in place

*/
void func1(int n, char ch)
{
int i,j;
for (i = 1; i <= n; i++)
{
	for (j = 1; j <= i; j++)
	{
		printf("%c ", ch);	
	}
	printf("\n");
}
}

void func2(int n, char ch)
{
int i,j;
for (i = 1; i <= n; i++)
{
	for (j = n; j >= i; j--)
	{
		printf("%c ", ch);	
	}
	printf("\n");
}
}

void func3(int n, char ch)
{
	func1(n, ch);
	func2(n-1, ch);
}

void func4(int n, char ch)
{
	int i,j,k;
	for ( i = 1; i <= n; i++)
	{
		for (j = 1; j <= n-i; j++)
			{
				printf(" ");
			}
		for (k = 1; k <= i; k++)
			{
				printf("%c " , ch);
			}
		printf("\n");	
	}
}
void func5(int n, char ch)
{
	/* j is space */
	int i,j,k;
	for ( i = 1; i <= n; i++)	
	{
		for (j = 1; j <= i-1; j++)
			{
				printf(" ");
			}
		for (k = n-i+1; k >= 1; k--)
			{
				printf("%c " , ch);
			}
		if(i != n)
		{
			printf("\n");	
		}

	}
}

void func6(int n, char ch)
{
	int i,j,k;
	func4(n, ch);
	/* j is space */
	for ( i = 1; i <= n; i++)	
	{
		for (j = 1; j <= i-1; j++)
			{
				printf(" ");
			}
		for (k = n-i+1; k > 1; k--)
			{
				printf(" %c" , ch);
			}
		if(i != n)
		{
			printf("\n");	
		}

	}
}
