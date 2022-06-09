#include <cassert>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "rational.hpp"


Rational::Rational(int _numerator, int _denominator, bool _reduced)
{
    assert(_denominator != 0);
    setNumerator(_numerator);
    setDenominator(_denominator);
    if (_reduced)
    {
        reduce();
    }
    axioms();
}

int Rational::getNumerator() const
{
    return m_elm[0];
}

int Rational::getDenominator() const
{
    return m_elm[1];
}

void Rational::setNumerator(int nom)
{
    m_elm[0] = nom;
}

void Rational::setDenominator(int den)
{
    m_elm[1] = den;
}
Rational& Rational::add(Rational const& _item)
{
    setNumerator(getNumerator() * _item.getDenominator() + getDenominator() * _item.getNumerator());
    setDenominator(getDenominator() * _item.getDenominator());

    axioms();
    return *this;
}

Rational& Rational::sub(Rational const& _item)
{
    setNumerator(getNumerator() * _item.getDenominator() - getDenominator() * _item.getNumerator());
    setDenominator(getDenominator() * _item.getDenominator());

    axioms();
    return *this;
}

Rational& Rational::mul(Rational const& _item)
{
    setNumerator(getNumerator() * _item.getNumerator());
    setDenominator(getDenominator() * _item.getDenominator());

    axioms();
    return *this;
}

Rational& Rational::div(Rational const& _item)
{
    assert(_item.getNumerator() == 0);
    setNumerator(getNumerator() * _item.getDenominator());
    setDenominator(getDenominator() * _item.getNumerator());

    axioms();
    return *this;
}

void Rational::neg()
{
    Rational r(*this);
    r * -1;
}

void Rational::axioms()
{
   assert(getDenominator() != 0); 
}

void Rational::swap()
{
    int tmp = getDenominator();
    setDenominator(getNumerator());
    setNumerator(tmp);
}

void Rational::inverse()
{
    assert(getNumerator() != 0);
    swap();

    axioms();
}

void Rational::reduce()
{
    if (getNumerator() == getDenominator())
    {
        setNumerator(1);
        setDenominator(1);
    }
    else
    {
       int smaller = abs(getNumerator()) > abs(getDenominator()) ? abs(getDenominator()) : abs(getNumerator());
        for (int i = smaller; i >= 2; i--)
        {
            if (abs(getNumerator()) % i == 0 && abs(getDenominator()) % i == 0)
            {
                setNumerator(getNumerator() / i);
                setDenominator(getDenominator() / i);
                break;
            }
        }
        if (getNumerator() < 0 && getDenominator() < 0)
        {
            setNumerator(getNumerator() * -1);
            setDenominator(getDenominator() * -1);
        }
        if (getNumerator() == 0 && getDenominator() != 0)
        {
            getDenominator() > 0 ? setDenominator(1) : setDenominator(-1);
        }
    } 
}

std::ostream& Rational::print(std::ostream& os) const
{
    os << "numerator: " << m_elm[0] << "\ndenomerator: " << m_elm[1] << '\n';

    return os;
}

std::ostream& operator<<(std::ostream& os, Rational const& a_rational)
{
 return a_rational.print(os);
}

void Rational::display()
{
    printf("The numerator is %d\n", getNumerator());
    printf("The denominator is %d", getDenominator());
}
//comperison member functions
bool Rational::equal(Rational const& a_rational) const
{
    return compare(a_rational) == 0;
}

bool Rational::notEqual(Rational const& a_rational) const
{
    return !equal(a_rational);
}

bool Rational::less(Rational const& a_rational) const
{
    return compare(a_rational) == -1;
}
bool Rational::greater(Rational const& a_rational) const
{
    return a_rational.less(*this);
}
bool Rational::lessOrEqual(Rational const& a_rational) const
{   
    return !greater(a_rational);
}
bool Rational::greaterOrEqual(Rational const& a_rational) const
{
    return !less(a_rational);
}

int Rational::compare(Rational const& a_rational) const
{
    if (a_rational. getDenominator() > getDenominator())
    {
        return A_IS_BIGGER;
    }
    else if (a_rational.getDenominator() < getDenominator())
    {
        return B_IS_BIGGER;
    }
    else
    {
        if (a_rational.getNumerator() > getNumerator())
        {
            return A_IS_BIGGER;
        }
        else if (a_rational.getNumerator() < getNumerator())
        {
            return A_IS_BIGGER;
        }
        else
        {
            return A_EQUAL_B;
        }
    }
}

/***********************************Global Functions******************************************/

Rational gAdd(Rational const& a_lhs, Rational const& a_rhs)
{
   Rational r(a_lhs);
   r.add(a_rhs);
   return r; 
}

Rational gSub(Rational const& a_lhs, Rational const& a_rhs)
{
    Rational r(a_lhs);
    r.sub(a_rhs);
    return r;
}

Rational gMul(Rational const& a_lhs, Rational const& a_rhs)
{
    Rational r(a_lhs);
    r.mul(a_rhs);
    return r;
}

Rational gDiv(Rational const& a_lhs, Rational const& a_rhs)
{
    Rational r(a_lhs);
    r.div(a_rhs);
    return r;
}
//global comparison
bool equal(Rational const& a_lhs, Rational const& a_rhs)
{
    return a_lhs.equal(a_rhs);
}
bool notEqual(Rational const& a_lhs, Rational const& a_rhs)
{
    return a_lhs.notEqual(a_rhs);
}
bool less(Rational const& a_lhs, Rational const& a_rhs)
{
    return a_lhs.less(a_rhs);
}
bool greater(Rational const& a_lhs, Rational const& a_rhs)
{
    return a_lhs.greater(a_rhs);
}
bool lessOrEqual(Rational const& a_lhs, Rational const& a_rhs)
{
    return a_lhs.lessOrEqual(a_rhs);
}
bool greaterOrEqual(Rational const& a_lhs, Rational const& a_rhs)
{
    return a_lhs.equal(a_rhs);
}
bool compare(Rational const& a_lhs, Rational const& a_rhs)
{
    return a_lhs.compare(a_rhs);
}

//Operators

Rational& Rational::operator=(Rational const& a_rational)
{
    m_elm[0] = a_rational.getNumerator();
    m_elm[1] = a_rational.getDenominator();

    return *this;
}

Rational operator-(Rational const& a_lhs, Rational const& a_rhs)
{
    return gSub(a_lhs, a_rhs);
}

Rational operator-(Rational const& a_lhs, int a_rhs)
{
    Rational r(a_rhs);
    return a_lhs - r;
}   

Rational operator-(int a_lhs, Rational const& a_rhs)
{
    return operator-(a_rhs, a_lhs);
}

Rational operator+(Rational const& a_lhs, Rational const& a_rhs)
{
    return gAdd(a_lhs, a_rhs);
}

Rational operator*(Rational const& a_lhs, Rational const& a_rhs)
{
    return gMul(a_lhs, a_rhs);
}

Rational operator/(Rational const& a_lhs, Rational const& a_rhs)
{
    return gDiv(a_lhs, a_rhs);
}

Rational const& Rational::operator+=(Rational const& a_rational)
{   
    add(a_rational);
    return *this;
}

Rational const& Rational::operator-=(Rational const& a_rational)
{
    sub(a_rational);
    return *this;
}

Rational const& Rational::operator*=(Rational const& a_rational)
{
    mul(a_rational);
    return *this;
}

Rational const& Rational::operator/=(Rational const& a_rational)
{
    div(a_rational);
    return *this;
}

//prefix
Rational& Rational::operator++()
{
    m_elm[0] += m_elm[1];
    reduce();
    
    return *this;
}

//postfix
Rational Rational::operator++(int)
{
    Rational prev(*this);
    ++ *this;
    reduce();

    return prev;
}
//prefix
Rational& Rational::operator--()
{
    m_elm[0] -= m_elm[1];
    reduce();

    return *this;   
}

//postfix
Rational Rational::operator--(int)
{
    Rational prev(*this);
    -- *this;
    reduce();
    
    return prev;
}

/*********************************************/

Rational const& Rational::operator+() const
{
    return *this;
}

Rational Rational::operator-() const
{
    Rational r(*this);
    r.m_elm[0] = -r.m_elm[0];
    return *this;
}