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

BigInteger::BigInteger(long a_num)
: m_digits()
{
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
        str += itr.getData();
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
    if(m_size > a_rhs.m_size)
    {
        ListItr itrSmall = a_rhs.begin();
        ListItr itrBig = m_digits.begin();
    }
    else
    {
        ListItr itrSmall = m_digits.begin();
        ListItr itrBig = a_rhs.begin();
    }

    short int carry = 0;

    while(itrSmall != NULL)
    {
        short int i = carry + itrSmall.getData() + itrBig.getData();
        carry = i / 10;
        temp.addFirst(i % 10);
        itrSmall.next();
        itrBig.next();
    }

    while(itrBig != NULL)
    {
        short int i = carry + itrBig.getData();
        carry = i / 10;
        temp.addFirst(i % 10);
        itrBig.next();
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


// BigInteger::BigInteger(int a_num){}


// BigInteger::BigInteger(long a_num)
// {

// }
// BigInteger::BigInteger(char a_num)
// {

// }

void BigInteger::toList(long a_num)
{
    int quot, div = a_num, rem;

    do{
        rem = div % 10;
        quot = div / 10;
        div = quot;

        m_digits.getHead()->setData(rem);
    }while(quot >= 10);

    if(quot > 0)
    {
        m_digits.getHead()->setData(rem);
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

//idea is to insert to the begining of list the digits of number from last to begin. using % and /.
