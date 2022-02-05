#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <math.h>
#include <cassert>
#include "big_integer.hpp"
#include "single_list.hpp"


BigInteger::BigInteger()
: m_digits()
, m_positive(true)
, m_size(m_digits.size())
{
    
}

BigInteger& BigInteger::operator=(const BigInteger& other)
{
    this->m_positive = other.m_positive;
    this->m_size = other.m_size;
    this->m_digits = other.m_digits;

    return *this;
}

BigInteger::BigInteger(char* a_str)
: m_digits()
{
    toList(string(a_str));
}

BigInteger::BigInteger(string a_str)
: m_digits()
{
    toList(a_str);
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

BigInteger::BigInteger(long a_num)
: m_digits()
, m_size()
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

bool BigInteger::isEmpty()
{
    return m_size == 0;
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
        str.push_back(itr.getData());
    }

    return str;
}

BigInteger::BigInteger(const BigInteger& a_bigNum)
{
    m_size = a_bigNum.getSize();
    m_positive = a_bigNum.isPositive();

    LinkedList bigNumDigits = a_bigNum.m_digits;

    for(ListItr itr = bigNumDigits.begin(); itr != bigNumDigits.end(); itr.next())
    {
        m_digits.addLast(itr.getData());
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

BigInteger BigInteger::add(BigInteger const& a_rhs)
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

    return temp;
}

BigInteger& BigInteger::sub(BigInteger const& a_rhs)
{
    return *this;
}

const BigInteger& BigInteger::operator=(BigInteger const& a_rhs)
{
    this->m_positive = a_rhs.m_positive;
    this->m_size = a_rhs.m_size;
    this->m_digits = a_rhs.m_digits;
    return *this;
}

BigInteger BigInteger::operator+=(BigInteger const& a_rhs)
{
    *this = add(a_rhs);
    return *this;
}

BigInteger BigInteger::operator+()
{
    return *this;
}

BigInteger BigInteger::operator-(){
    if (size > 0)
        n_positive = (isPositive()) ? false : true;
    return *this;
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
        m_digits.addLast((short int)quot);
    }
}

void BigInteger::toList(string a_str)
{
    int strLength = a_str.length();
    assert(strLength > 0);
    m_size = 0;

    if(strLength == 1)
    {
        char c = a_str[0];
        assert(c > '0' || c < '9');
        m_digits.addFirst((short int)(c - '0'));
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

        m_digits.addLast((short int)(c - '0'));
        m_size++;
    }
}

bool BigInteger::isPositive() const
{
    return m_positive;
}

int BigInteger::getSize() const
{
    return m_size;
    
}