#include "point.hpp"

using cpp::Point;

template <typename T>
Point<T>::Point(T a_x, T a_y)
: m_x(a_x)
, m_y(a_y)
{}

template <typename T>
void Point<T>::setX(T a_x)
{
    m_x = a_x;
}

template <typename T>
void Point<T>::setY(T a_y)
{
    m_y = a_y;
}

template <typename T>
T const& Point<T>::getX() const
{
    return m_x;
}

template <typename T>
T const& Point<T>::getY() const
{
    return m_y;
}

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
bool Point<T>::compareX(T const& point1 , T const& point2)
{
    if(point1.x < point2.x)
    {
        return true;
    }
    else if(point1.getX == point2.x)
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
    return (m_x*m_x + m_y*m_y < a_rhs.m_x*a_rhs.getX() + a_rhs.m_y*getY());
}

template <typename T>
double Point<T>::distance(Point<T>& point1 , Point<T>& point2) 
{
	return sqrt((point1.m_x - point2.m_x) * (point1.m_x - point2.m_x) + (point1.m_y - point2.m_y) * (point1.m_y - point2.m_y));
}
