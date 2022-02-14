#ifndef POINT_HPP
#define POINT_HPP

#include <cstddef>
#include <cmath>

template <typename T>
class Point
{
public:
    T* m_arr;
    T x,y;
public:
    bool operator<(Point<T> const& a_rhs) const;

    T const& operator[](size_t a_index) const;
    T& operator[](size_t a_index);
};

template <typename T>
T const& Point<T>::operator[](size_t a_index) const
{
    return m_arr[a_index];
}

template <typename T>
T& Point<T>::operator[](size_t a_index)
{
    return m_arr[a_index];
}

template <typename T>
bool compareX(T const& point1 , T const& point2)
{
    if(point1.x < point2.x)
    {
        return true;
    }
    else if(point1.x == point2.x)
    {
        return point1.y < point2.y;
    } 
    else
    {
        return false ;
    }   
}

template <typename T>
bool Point<T>::operator<(Point<T> const& a_rhs) const
{
    return this->x < a_rhs.x;
}

template <typename T>
double distance(Point<T>& point1 , Point<T>& point2) 
{
	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

#endif /*POINT_HPP*/