#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <math.h>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include "big_integer.hpp"
#include "single_list.hpp"


BigInteger::BigInteger()
: m_digits()
, m_positive(true)
{}

BigInteger::BigInteger(BigInteger const& a_bigNum)
{
    m_size = a_bigNum.getSize();
    m_positive = a_bigNum.isPositive();

    LinkedList bigNumDigits = a_bigNum.m_digits;
    for(ListItr itr = bigNumDigits.begin(); itr != bigNumDigits.end(); itr.next())
    {
        m_digits.addLast(itr.getData());
    }
}

BigInteger::BigInteger(const char* a_str)
{
    toList(string(a_str));
}

BigInteger::BigInteger(const string a_str)
{
    toList(a_str);
}

BigInteger::BigInteger(long a_num)
{
    // flip(a_num);
    if(a_num >= 0)
    {
        m_positive = true;
    }
    else
    {
        m_positive = false;
        a_num *= - 1;
    }

    if(a_num >= 0 && a_num < 10)
    {
        m_digits.addLast(a_num);
    }
    else
    {
        toList(a_num);
    }

    m_size = m_digits.size();
}

// void BigInteger::flip(long &a_num)
// {
//     size_t remainder;
//     size_t reverseNum = 0;
//     while(a_num != 0) 
//     {
//         remainder = a_num % 10;
//         reverseNum = reverseNum * 10 + reverseNum;
//         a_num /= 10;
//     }
// }

void BigInteger::flip(long &a_num)
{   
    return flip(a_num * 10) + flip(a_num % 10);
}

string BigInteger::toString()
{
    if(m_size == 0)
    {
        return "";
    }
    string str;
    if(isPositive() == false)
    {
        str.append("-");
    }
    
    for(ListItr itr = m_digits.begin(); itr != m_digits.end(); itr.next())
    {
        str += itr.getData();
        printf("%s ", str.c_str());
    }

    return str;
}

void BigInteger::toList(long a_num)
{
    int quot, div = a_num;
    short int rem;

    do{
        rem = div % 10;
        quot = div / 10;
        div = quot;

        m_digits.addLast(rem);
    }while(quot >= 10);

    if(quot > 0)
    {
        m_digits.addLast(quot);
    }
}

void BigInteger::toList(string a_str)
{
    int strLength = a_str.length();
    assert(strLength > 0);
    int zero = int('0');
    m_size = 0;

    if(strLength == 1)
    {
        char c = a_str[0];
        assert(c > '0' || c < '9');
        m_digits.addFirst((short int)(c - zero));
        m_size++;
        return;
    }

    if(a_str[0] == '-')
    {
        m_positive = false;
    }

    int begin = m_positive ? 0 : 1;

    for(int i = begin; i < strLength; i++)
    {
        char c = a_str[i];
        assert(c > '0' || c < '9');

        if(m_size == 0 && c == '0')
        {
            continue;
        }

        m_digits.addLast((short int)(c - zero));
        m_size++;
    }
}

ListItr BigInteger::begin() const
{
    return m_digits.begin();
}

ListItr BigInteger::end() const
{
    return m_digits.end();
}

void BigInteger::addFirst(const short int a_calc)
{
    m_digits.addFirst(a_calc);          
    m_size = m_digits.size();
}
void BigInteger::addLast(const short int a_calc)
{
    m_digits.addLast(a_calc);
    m_size = m_digits.size();
}

BigInteger& BigInteger::add(BigInteger const& a_rhs)
{
    if(this->isPositive() ^ a_rhs.isPositive())
    {
        return sub(a_rhs);
    }

    BigInteger temp;
    ListItr itrSmall, itrBig;
    size_t smallSize,bigSize;
    
    if(this->m_size > a_rhs.m_digits.size())
    {
        itrSmall = a_rhs.begin();
        itrBig = m_digits.begin();
        smallSize = a_rhs.getSize()-1;
        bigSize = m_digits.size()-1;
        
    }
    else
    {
        itrSmall = m_digits.begin();
        itrBig = a_rhs.begin().next();
        smallSize = m_digits.size()-1;
        bigSize = a_rhs.getSize()-1;
         
    }

    short int carry = 0;
    short int i;
    while(smallSize > 0)
    {
        i = carry + itrSmall.getData() + itrBig.getData();
        carry = i / 10;
        temp.addFirst(i % 10);
        itrSmall.next();
        itrBig.next();
        smallSize--;
    }
    while(bigSize > 0)
    {
        i = carry + itrBig.getData();
        carry = i / 10;
        temp.addFirst(i % 10);
        itrBig.next();
        bigSize--;
    }

    if(carry)
    {
        temp.addFirst(carry);
    }

    return *this;
}

BigInteger& BigInteger::sub(BigInteger const& a_rhs)
{
    return *this;
}


int BigInteger::equals(const BigInteger& other) const
{
    bool sign1 = isPositive();
    bool sign2 = other.isPositive();

    if(sign1 ^ sign2){
        if (sign1 && !sign2)
            return 1;
        else
            return -1;
    }
    
    //signs same, size different
    int size1 = getSize();
    int size2 = other.getSize();
    
    if (size1 ^ size2)
	{
        if (size1 > size2)
		{
			return (sign1) ? 1 : -1;
		}
            
        else
		{
			return (!sign1) ? 1 : -1;
		}    
    }
    
    //signs and size are the same
    for(ListItr itr1 = begin(), itr2 = other.begin(); itr1 != end(); itr1.next(), itr2.next())
	{
        if (itr1.getData() == itr2.getData())
		{
			continue;
		}
        if (itr1.getData() > itr2.getData())
		{
			return (sign1) ? 1 : -1;
		}   
        else
		{
			return (!sign1) ? 1 : -1;
		}
            
    }
	
    return 0;
}

BigInteger& BigInteger::operator=(BigInteger const& a_rhs)
{
    this->m_positive = a_rhs.m_positive;
    this->m_size = a_rhs.m_size;
    this->m_digits = a_rhs.m_digits;
    return *this;
}

BigInteger BigInteger::operator+=(BigInteger const& a_rhs)
{
    return add(a_rhs);
}

BigInteger BigInteger::operator+()
{
    return *this;
}

BigInteger BigInteger::operator-()
{
    if (m_size > 0)
    {
        m_positive = (isPositive()) ? false : true;
    }

    return *this;
}

bool equal(BigInteger const& a_lhs, BigInteger const& a_rhs)
{
    return a_lhs.equals(a_rhs) == 0;
}

bool notEqual(BigInteger const& a_lhs, BigInteger const& a_rhs)
{
    return !equal(a_lhs, a_rhs);
}

bool equal(BigInteger const& a_lhs, long a_rhs)
{
    return a_lhs.equals(a_rhs) == 0;
}

bool notEqual(BigInteger const& a_lhs, long a_rhs)
{
    return !equal(a_lhs, a_rhs);
}

bool greaterthan(BigInteger const& a_lhs, BigInteger const& a_rhs)
{
    return lessthan(a_rhs, a_lhs);
}

bool lessthan(BigInteger const& a_lhs, BigInteger const& a_rhs)
{
    return (a_lhs.equals(a_rhs) < 0) ? true : false;
}

bool greaterOrEqual(BigInteger const& a_lhs, BigInteger const& a_rhs)
{
    return !lessthan(a_lhs, a_rhs);
}

bool lessOrEqual(BigInteger const& a_lhs, BigInteger const& a_rhs)
{
    return !greaterthan(a_lhs, a_rhs);
}

bool BigInteger::isPositive() const
{
    return m_positive;
}

int BigInteger::getSize() const
{
    return m_size;
}

bool BigInteger::isEmpty() const
{
    return m_size == 0;
}