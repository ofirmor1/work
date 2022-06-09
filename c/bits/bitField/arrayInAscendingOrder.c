#include <stdio.h>
#include <time.h>
#define SIZE 50000


int main (void)
{
	clock_t t1, t2;
	int randArray1[SIZE],i,randArray2[SIZE];
	for(i=0;i<SIZE;i++)
	{
    randArray1[i]=rand()%50000;
	randArray2[i]= randArray1[i]; /*Generate number between 0 to 99*/
	}
	t1=clock();
	FuncarrayInAscendingOrder(randArray1,SIZE);
	t2=clock();
	printf("function: %f\n", (float)(t2-t1)/1000000);
	
	t1=clock();
	FuncarrayInAscendingOrderSWAP(randArray2,SIZE);
	t2=clock();
	printf("MACRO: %f\n", (float)(t2-t1)/1000000);
	/*printArray(ptr,SizeOfArr);*/

}
