/*#include <stdio.h>

int Power(int _n, int _k)
{
	if(_k == 0)
	{
		return 1;
	}
	return Power(_n, _k-1)*_n;
}

int main(void)
{
	int num;
	num = Power(3,2);
	printf("%d \n", num);
}
*/

#include <stdio.h>

int Power(int _n, int _k)
{
	int sign = 1;
	if(_k < 0)
	{
		sign = -1;
		k *= -1;
	}
	if(_k == 0)
	{
		return 1;
	}
	return Power(_n, _k-1)*_n;
}

int main(void)
{
	int num;
	num = Power(3,2);
	printf("%d \n", num);
}
