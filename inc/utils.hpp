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

#endif /*ifndef UTILS_HPP*/