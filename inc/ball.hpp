#ifndef BALL_HPP
#define BALL_HPP

class Ball
{
public:
    const char* m_color;
    double m_radius;

    bool operator<(Ball const& a_rhs) const;
};

bool Ball::operator<(Ball const& a_rhs) const
{
    return this->m_radius < a_rhs.m_radius;
}

#endif /*BALL_HPP*/