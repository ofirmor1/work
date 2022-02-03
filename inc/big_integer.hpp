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

    BigInteger(const BigInteger& a_big);
    BigInteger& operator=(const BigInteger&);

    BigInteger(long a_num);
    BigInteger(char* a_num);
    BigInteger(string a_str);

    bool isPositive() const;
    int getSize() const;
    void addFirst(const short int a_calc);
    void addLast(const short int a_calc);


    string toString();
    bool isEmpty();

private:
    BigInteger add(BigInteger const& a_rhs);
    BigInteger& sub(BigInteger const& a_rhs);
    BigInteger& mul(BigInteger const& a_rhs);

    ListItr begin() const;
    ListItr end() const;

    void toList(long a_num);
    void toList(string a_num);

private:
    LinkedList m_digits;
    bool m_positive;
    int m_size;
};

BigInteger add(BigInteger const& a_lhs, BigInteger const& a_rhs);
void add(BigInteger const& a_lhs, BigInteger const& a_rhs, BigInteger const& a_sum);

#endif /*BIG_INTEGER_HPP*/