#include "ball.hpp"

using cpp::Ball;

Ball::Ball()
{}

Ball::Ball(const char* a_color, double a_radius)
: m_color(a_color)
, m_radius(a_radius)
{}

double Ball::getRadius() const
{
    return m_radius;
}

inline
const char* Ball::getColor() const
{
    return m_color;
}


bool Ball::operator<(Ball const& a_rhs) const
{
    return this->m_radius < a_rhs.m_radius;
}

bool Ball::operator>(Ball const& a_rhs) const
{
    return this->m_radius > a_rhs.m_radius;
}

bool Ball::operator==(Ball const& a_rhs) const
{
    return this->m_radius == a_rhs.m_radius;
}

