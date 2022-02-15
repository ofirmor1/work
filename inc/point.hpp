#ifndef POINT_HPP
#define POINT_HPP

#include <cstddef>
#include <cmath>

namespace cpp
{
template <typename T>
class Point
{
public:
    Point<T>(T a_x, T a_y);
    bool operator<(Point<T> const& a_rhs) const;

    T const& operator[](size_t a_index) const;
    T& operator[](size_t a_index);

    bool compareX(T const& point1 , T const& point2);
    double distance(Point<T>& point1 , Point<T>& point2);

    void setX(T a_x);
    void setY(T a_y);

    T const& getX() const;
    T const& getY() const;

private:
    T* m_arr;
    T m_x,m_y;

};

} // namespace name


#include "point.hxx"

#endif /*POINT_HPP*/