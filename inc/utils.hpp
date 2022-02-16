#ifndef UTILS_HPP
#define UTILS_HPP

template <typename T>
void swap(T& a_first, T& a_second)
{
    T temp = a_first;
    a_first = a_second;
    a_second = temp;
    // a_first = a_first + a_second;
    // a_second = a_first - a_second;
    // a_first = a_first - a_second;
}

int* randIntArr(const size_t N)
{
    int* arr = new int[N];
    for(size_t i = 0; i < N; i++)
    {
        arr[i] = rand() % 10;
    }
    
    return arr;
}

    

#endif /*ifndef UTILS_HPP*/