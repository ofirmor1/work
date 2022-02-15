#ifndef BALL_HPP
#define BALL_HPP

namespace cpp
{

class Ball
{
public:
    Ball(const char* a_color, double a_radius);
    // const char *m_color();
    double getRadius() const;
    const char* getColor() const;
    bool operator<(Ball const &a_rhs) const;

private:
    void axioms() const;

private:
    const char *m_color;
    double m_radius;
};

} // namespace cpp

#include "ball.hxx"

#endif /*BALL_HPP*/