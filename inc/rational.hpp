#ifndef RATIONAL_H
#define RATIONAL_H

enum Compare{A_IS_BIGGER = 1, B_IS_BIGGER = -1 , A_EQUAL_B = 0};

class Rational
{
public:
    // reduced representation of a rational
    Rational(int _nominator = 0, int _denominator = 1, bool reduced = true);


    void inverse();
    void reduce();
    void display();
    void neg();

    int getNumerator() const;
    int getDenominator() const;

    bool equal(Rational a) const;
    bool notEqual(Rational a) const;
    int compare(Rational a) const;


    void setNumerator(int v);
    void setDenominator(int v);

    void add(Rational _item);
    void sub(Rational _item);
    void mul(Rational _item);
    void div(Rational _item);

    Rational& operator=(Rational const& a_rational);
    Rational operator==(Rational const& a_rhs) const;
    Rational operator!=(Rational const& a_rhs) const;
    Rational operator<=(Rational const& a_rhs) const;
    Rational operator>=(Rational const& a_rhs) const;
    Rational operator<(Rational const& a_rhs) const;
    Rational operator>(Rational const& a_rhs) const;
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);
    Rational& operator-(Rational const& a_rhs) const;
    Rational& operator+(Rational const& a_rhs) const;
    
private:

    int m_elm[2];
    void swap();
    void axioms();
};

bool equal(Rational a);


Rational gAdd(Rational a, Rational b);  
Rational gSub(Rational a, Rational b); 
Rational gMul(Rational a, Rational b); 
Rational gDiv(Rational a, Rational b); 

Rational operator+=(Rational const& a_first, Rational const& a_second);
Rational operator-=(Rational const& a_first, Rational const& a_second);
Rational operator*=(Rational const& a_first, Rational const& a_second);
Rational operator/=(Rational const& a_first, Rational const& a_second);
Rational operator*(Rational const& a_first, Rational const& a_second);
Rational operator/(Rational const& a_first, Rational const& a_second);
Rational operator+(Rational const& a_first, Rational const& a_second);
Rational operator-(Rational const& a_first, Rational const& a_second);
Rational operator-(Rational const& a_first, int a_num);
Rational operator-(int a_num, Rational const& a_first);


#endif /*#ifndef RATIONAL_H*/