#include <cassert>
#include "../inc/Rational.hpp"
#include <cassert>
#include <cstdlib>
#include <stdio.h>

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
void Rational::add(Rational _item)
{
    setNumerator(getNumerator() * _item.getDenominator() + getDenominator() * _item.getNumerator());
    setDenominator(getDenominator() * _item.getDenominator());

    axioms();
}

void Rational::sub(Rational _item)
{
    setNumerator(getNumerator() * _item.getDenominator() - getDenominator() * _item.getNumerator());
    setDenominator(getDenominator() * _item.getDenominator());

    axioms();
}

void Rational::mul(Rational _item)
{
    setNumerator(getNumerator() * _item.getNumerator());
    setDenominator(getDenominator() * _item.getDenominator());

    axioms();
}

void Rational::div(Rational _item)
{
    assert(_item.getNumerator() == 0);
    setNumerator(getNumerator() * _item.getDenominator());
    setDenominator(getDenominator() * _item.getNumerator());

    axioms();
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
       int smaller = getNumerator() > getDenominator() ? abs(getDenominator()) : abs(getNumerator());
        for (int i = smaller; i >= 2; i--)
        {
            if (abs(getNumerator()) % i == 0 && abs(getDenominator()) % i == 0)
            {
                display();
                setNumerator(abs(getNumerator()) / i);
                setDenominator(abs(getDenominator()) / i);
                break;
            }
        }
        if (getNumerator() < 0 && getDenominator() < 0)
        {
            setNumerator(getNumerator() * -1);
            setDenominator(getDenominator() * -1);
        }
    } 
}

void Rational::display()
{
    printf("The numerator is %d\n", getNumerator());
    printf("The denominator is %d", getDenominator());
}

bool Rational::equal(Rational a) const
{
    return (getNumerator() == a.getNumerator() && getDenominator() == a.getDenominator());
}

bool Rational::notEqual(Rational a) const
{
    return !equal(a);
}
int Rational::compare(Rational a) const
{
    if (a. getDenominator() > getDenominator())
    {
        return A_IS_BIGGER;
    }
    else if (a.getDenominator() < getDenominator())
    {
        return B_IS_BIGGER;
    }
    else
    {
        if (a.getNumerator() > getNumerator())
        {
            return A_IS_BIGGER;
        }
        else if (a.getNumerator() < getNumerator())
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

Rational gAdd(Rational first, Rational second)
{
    first.add(second);
    return first;
}

Rational gSub(Rational first, Rational second)
{
    first.sub(second);
    return first;
}

Rational gMul(Rational first, Rational second)
{
    first.mul(second);
    return first;
}

Rational gDiv(Rational first, Rational second)
{
    first.div(second);
    return first;
}

void Rational::axioms()
{
   assert(getDenominator() != 0); 
}

