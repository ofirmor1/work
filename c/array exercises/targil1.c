#include <stdio.h>

int Add(int _a, int _b)
{
	return _a + _b;
}

int Sub(int _a, int _b)
{
	return _a - _b;
}
int Mul(int _a, int _b)
{
	return _a * _b;
}

int main(void)
{
	int sum, dif,mul,x,y;
	printf("Please enter 2 numbers: \n");
	scanf("%d %d", &x, &y);
	sum = Add(x,y);
	dif = Sub(x,y);
	mul = Mul(x,y);
	printf("%d + %d = %d\n", x, y, Add(x,y));
	printf("%d - %d = %d\n", x, y, Sub(x,y));
	printf("%d * %d = %d\n", x, y, Mul(x,y));
	
	return 0;
}
