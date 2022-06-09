#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

enum Compare{A_IS_BIGGER = 1, B_IS_BIGGER = -1 , A_EQUAL_B = 0};

class Rational
{
public:
    // reduced representation of a rational
    Rational(int _nominator = 0, int _denominator = 1, bool reduced = true);
    
    void neg();
    void inverse();
    void reduce();
    void display();

    int getNumerator() const;
    int getDenominator() const;

    bool equal(Rational const& a_rational) const;
    bool notEqual(Rational const& a_rational) const;
    bool less(Rational const& a_rational) const;
    bool greater(Rational const& a_rational) const;
    bool lessOrEqual(Rational const& a_rational) const;
    bool greaterOrEqual(Rational const& a_rational) const;
    int compare(Rational const& a_rational) const;

    void setNumerator(int v);
    void setDenominator(int v);

    Rational& add(Rational const& a_rational);
    Rational& sub(Rational const& a_rational);
    Rational& mul(Rational const& a_rational);
    Rational& div(Rational const& a_rational);

    Rational& operator=(Rational const& a_rational);

    Rational const& operator+=(Rational const& a_rational);
    Rational const& operator-=(Rational const& a_rational);
    Rational const& operator*=(Rational const& a_rational);
    Rational const& operator/=(Rational const& a_rational);

    bool operator==(Rational const& a_rhs) const;
    bool operator!=(Rational const& a_rhs) const;
    bool operator<=(Rational const& a_rhs) const;
    bool operator>=(Rational const& a_rhs) const;
    bool operator<(Rational const& a_rhs) const;
    bool operator>(Rational const& a_rhs) const;

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    Rational operator-() const;
    Rational const& operator+() const;

    std::ostream& print(std::ostream& os) const;
    
private:

    int m_elm[2];
    void swap();
    void axioms();
};

bool equal(Rational const& a_lhs, Rational const& a_rhs);
bool notEqual(Rational const& a_lhs, Rational const& a_rhs);
bool less(Rational const& a_lhs, Rational const& a_rhs);
bool greater(Rational const& a_lhs, Rational const& a_rhs);
bool lessOrEqual(Rational const& a_lhs, Rational const& a_rhs);
bool greaterOrEqual(Rational const& a_lhs, Rational const& a_rhs);
bool compare(Rational const& a_lhs, Rational const& a_rhs); 

Rational gAdd(Rational const& a_lhs, Rational const& a_rhs);  
Rational gSub(Rational const& a_lhs, Rational const& a_rhs); 
Rational gMul(Rational const& a_lhs, Rational const& a_rhs); 
Rational gDiv(Rational const& a_lhs, Rational const& a_rhs); 

Rational operator*(Rational const& a_lhs, Rational const& a_rhs);
Rational operator/(Rational const& a_lhs, Rational const& a_rhs);
Rational operator+(Rational const& a_lhs, Rational const& a_rhs);
Rational operator-(Rational const& a_lhs, Rational const& a_rhs);
Rational operator-(Rational const& a_lhs, int a_num);
Rational operator-(int a_num, Rational const& a_rhs);

std::ostream& operator<<(std::ostream& os, Rational const& a_rational);

#endif /*#ifndef RATIONAL_H*/