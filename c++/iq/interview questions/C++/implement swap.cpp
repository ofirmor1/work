#include <iostream>

void swap(int* a,int* b){
	int temp = *b;
	*b = *a;
	*a = temp;
	return;
}

void swap2(int* a,int* b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap3(int* a,int* b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main()
{
    int x = 3;
    int y = 4;

    swap(&x, &y);

    std::cout << "swap 1 | x: " << x << " y: " << y << '\n';

    swap2(&x, &y);

    std::cout << "swap 2 | x: " << x << " y: " << y << '\n';

    swap3(&x, &y);

    std::cout << "swap 3 | x: " << x << " y: " << y << '\n';

}