#ifndef BALL_HPP
#define BALL_HPP

namespace cpp
{

class Ball
{
public:
    Ball();
    Ball(const char* a_color, double a_radius);
    // const char *m_color();
    double getRadius() const;
    const char* getColor() const;
    bool operator<(Ball const &a_rhs) const;
    bool operator>(Ball const &a_rhs) const;
    bool operator==(Ball const& a_rhs) const;

private:
    void axioms() const;

private:
    const char *m_color;
    double m_radius;
};

std::ostream& operator<<(std::ostream& os, Ball const& ball)
{
    return os << "(" << ball.getRadius() << ", " << ball.getColor() << ")";
}

} // namespace cpp

#include "inl/ball.hxx"

#endif /*BALL_HPP*/
