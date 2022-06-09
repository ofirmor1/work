#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <iostream>
/*#include <sstream>*/
#include <string>
#include "single_list.hpp"

class BigInteger
{
public:
    BigInteger();

    BigInteger(BigInteger const& a_big);
    
    BigInteger(const long a_num);
    BigInteger(const char* a_num);
    BigInteger(const string a_str);

    bool isPositive() const;
    int getSize() const;
    void addFirst(const short int a_calc);
    void addLast(const short int a_calc);

    BigInteger& add(BigInteger const& a_rhs);
    BigInteger& sub(BigInteger const& a_rhs);
    BigInteger& mul(BigInteger const& a_rhs);

    int equals(const BigInteger& other) const;
    BigInteger& operator=(BigInteger const& a_rhs);
    BigInteger operator+=(BigInteger const& a_rhs);
    BigInteger operator+();
    BigInteger operator-();

    string toString();
    bool isEmpty() const;

private:

    ListItr begin() const;
    ListItr end() const;

    void toList(long a_num);
    void toList(string a_num);

    void flip(long &a_num);

private:
    LinkedList m_digits;
    bool m_positive;
    int m_size;
};

BigInteger add(BigInteger const& a_lhs, BigInteger const& a_rhs);
void add(BigInteger const& a_lhs, BigInteger const& a_rhs, BigInteger const& a_sum);

bool equal(BigInteger const& bigNum1, BigInteger const& bigNum2);
bool notEqual(BigInteger const& bigNum1, BigInteger const& bigNum2);

bool equal(BigInteger const& bigNum1, long bigNum2);
bool notEqual(BigInteger const& bigNum1, long bigNum2);

bool greaterOrEqual(BigInteger const& bigNum1, BigInteger const& bigNum2);
bool lessOrEqual(BigInteger const& bigNum1, BigInteger const& bigNum2);

bool greaterthan(BigInteger const& bigNum1, BigInteger const& bigNum2);
bool lessthan(BigInteger const& bigNum1, BigInteger const& bigNum2);

#endif /*BIG_INTEGER_HPP*/