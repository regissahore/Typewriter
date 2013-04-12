#include <QtDebug>
#include <QTextStream>
#include <QString>
#include "biginteger.h"

/**
 * The integer is set to 0 when initializing.
 */
BigInteger::BigInteger()
{
    this->_positive = true;
    this->_data.push_back(0);
}

BigInteger::~BigInteger()
{
    this->_data.clear();
}

/**
 * Parse the integer value to BigInteger.
 * Let n be the digit number of the integer value, the time complexity is about O(n).
 * @param value The integer value.
 * @return The big integer.
 */
BigInteger BigInteger::valueOf(int value)
{
    BigInteger bigInteger;
    if (value < 0)
    {
        bigInteger._positive = false;
        value = - value;
    }
    if (value > 0)
    {
        bigInteger._data.clear();
        while (value > 0)
        {
            bigInteger._data.push_back(value % 10000);
            value /= 10000;
        }
    }
    return bigInteger;
}

/**
 * Parse the string value to big integer.
 * Let n be the length of string, the time complexity is about O(n).
 * @param value The string should contains only number and negative operator.
 * @return The big integer.
 */
BigInteger BigInteger::valueOf(QString value)
{
    BigInteger bigInteger;
    if (value.at(0) == '-')
    {
        bigInteger._positive = false;
        value = value.right(value.length() - 1);
    }
    bigInteger._data.clear();
    for (int end = value.length(); end > 0; end -= 4)
    {
        int start = end - 4;
        if (start < 0)
        {
            start = 0;
        }
        int temp = 0;
        for (int i = start; i < end; ++i)
        {
            temp = temp * 10 + (value.at(i).unicode() - '0');
        }
        bigInteger._data.push_back(temp);
    }
    bigInteger.clearLeadingZero();
    return bigInteger;
}

BigInteger BigInteger::zero()
{
    return valueOf(0);
}

BigInteger BigInteger::one()
{
    return valueOf(1);
}

int BigInteger::digitNum() const
{
    int num = (this->_data.size() - 1) * 4;
    int last = this->_data[this->_data.size() - 1];
    if (last < 10)
    {
        num += 1;
    }
    else if (last < 100)
    {
        num += 2;
    }
    else if (last < 1000)
    {
        num += 3;
    }
    else
    {
        num += 4;
    }
    return num;
}

bool BigInteger::positive() const
{
    return this->_positive;
}

BigInteger BigInteger::copy() const
{
    return (*this);
}

BigInteger BigInteger::opposite() const
{
    BigInteger integer = this->copy();
    integer._positive = !this->_positive;
    return integer;
}

BigInteger BigInteger::absolute() const
{
    if (!this->_positive)
    {
        return this->copy().opposite();
    }
    return this->copy();
}

/**
 * Let n be the digit number of the big integer, the time complexity is about O(n).
 * @return The half value.
 */
BigInteger BigInteger::half() const
{
    BigInteger integer;
    integer._positive = this->_positive;
    int carry = 0;
    integer._data.clear();
    for (int i = this->_data.size() - 1; i >= 0; --i)
    {
        integer._data.push_front((this->_data.at(i) >> 1) + carry);
        carry = 0;
        if (this->_data.at(i) & 1)
        {
            carry = 5000;
        }
    }
    integer.clearLeadingZero();
    return integer;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(max(n, m)).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The compare result.
 */
bool operator ==(const BigInteger &a, const BigInteger &b)
{
    if (a._data.size() == 1 && b._data.size() == 1)
    {
        if (a._data.at(0) == 0 && b._data.at(0) == 0)
        {
            return true;
        }
    }
    if (a._positive != b._positive)
    {
        return false;
    }
    if (a._data.size() != b._data.size())
    {
        return false;
    }
    for (int i = 0; i < a._data.size(); ++i)
    {
        if (a._data.at(i) != b._data.at(i))
        {
            return false;
        }
    }
    return true;
}


bool operator !=(const BigInteger &a, const BigInteger &b)
{
    return !(a == b);
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(max(n, m)).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The compare result.
 */
bool operator <(const BigInteger &a, const BigInteger &b)
{
    if (a == BigInteger::zero() && b == BigInteger::zero())
    {
        return false;
    }
    if (a._positive != b._positive)
    {
        if (a._positive)
        {
            return false;
        }
        return true;
    }
    if (a._positive)
    {
        if (a._data.size() < b._data.size())
        {
            return true;
        }
        if (a._data.size() > b._data.size())
        {
            return false;
        }
        for (int i = a._data.size() - 1; i >= 0; --i)
        {
            if (a._data.at(i) < b._data.at(i))
            {
                return true;
            }
            if (a._data.at(i) > b._data.at(i))
            {
                return false;
            }
        }
        return false;
    }
    return a.opposite() > b.opposite();
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(max(n, m)).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The compare result.
 */
bool operator >(const BigInteger &a, const BigInteger &b)
{
    return b < a;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(max(n, m)).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The compare result.
 */
bool operator <=(const BigInteger &a, const BigInteger &b)
{
    return a < b || a == b;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(max(n, m)).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The compare result.
 */
bool operator >=(const BigInteger &a, const BigInteger &b)
{
    return a > b || a == b;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(max(n, m)).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The operate result.
 */
BigInteger operator +(const BigInteger &a, const BigInteger &b)
{
    BigInteger c;
    if (a._positive && !b._positive)
    {
        c = a - b.opposite();
    }
    else if (!a._positive && b._positive)
    {
        c = b - a.opposite();
    }
    else
    {
        c._positive = a._positive;
        int minLen, maxLen;
        if (a._data.size() < b._data.size())
        {
            minLen = a._data.size();
            maxLen = b._data.size();
        }
        else
        {
            minLen = b._data.size();
            maxLen = a._data.size();
        }
        int carry = 0;
        c._data.clear();
        for (int i = 0; i < minLen; ++i)
        {
            int value = a._data.at(i) + b._data.at(i) + carry;
            carry = 0;
            if (value >= 10000)
            {
                value -= 10000;
                carry = 1;
            }
            c._data.push_back(value);
        }
        for (int i = minLen; i < maxLen; ++i)
        {
            int value;
            if (a._data.size() > b._data.size())
            {
                value = a._data.at(i) + carry;
            }
            else
            {
                value = b._data.at(i) + carry;
            }
            carry = 0;
            if (value >= 10000)
            {
                value -= 10000;
                carry = 1;
            }
            c._data.push_back(value);
        }
        if (carry > 0)
        {
            c._data.push_back(1);
        }
    }
    return c;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(max(n, m)).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The operate result.
 */
BigInteger operator -(const BigInteger &a, const BigInteger &b)
{
    BigInteger c;
    if (a._positive != b._positive)
    {
        c = a + b.opposite();
    }
    else if (a._positive)
    {
        if (a < b)
        {
            c = (b - a).opposite();
        }
        else
        {
            int carry = 0;
            c._data.clear();
            for (int i = 0; i < b._data.size(); ++i)
            {
                int value = a._data.at(i) - b._data.at(i) - carry;
                carry = 0;
                if (value < 0)
                {
                    value += 10000;
                    carry = 1;
                }
                c._data.push_back(value);
            }
            for (int i = b._data.size(); i < a._data.size(); ++i)
            {
                int value = a._data.at(i) - carry;
                carry = 0;
                if (value < 0)
                {
                    value += 10000;
                    carry = 1;
                }
                c._data.push_back(value);
            }
        }
    }
    else
    {
        c = b.opposite() - a.opposite();
    }
    c.clearLeadingZero();
    return c;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(n * m).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The operate result.
 */
BigInteger operator *(const BigInteger &a, const BigInteger &b)
{
    BigInteger c;
    if (a._positive != b._positive)
    {
        c._positive = false;
    }
    c._data.clear();
    for (int i = 0; i < a._data.size() + b._data.size(); ++i)
    {
        c._data.push_back(0);
    }
    for (int i = 0; i < a._data.size(); ++i)
    {
        for (int j = 0; j < b._data.size(); ++j)
        {
            int pos = i + j;
            c._data[pos] += a._data.at(i) * b._data.at(j);
            while (c._data[pos] >= 10000)
            {
                c._data[pos + 1] += c._data[pos] / 10000;
                c._data[pos] %= 10000;
                ++pos;
            }
        }
    }
    c.clearLeadingZero();
    return c;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(log(n) * m * n).
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The operate result.
 */
BigInteger operator /(const BigInteger &a, const BigInteger &b)
{
    BigInteger c;
    if (a._positive != b._positive)
    {
        c._positive = false;
    }
    BigInteger aa = a.absolute();
    BigInteger bb = b.absolute();
    if (aa >= bb)
    {
        BigInteger left = BigInteger::one();
        BigInteger right = aa;
        while (left <= right)
        {
            BigInteger mid = (left + right).half();
            BigInteger temp = bb * mid;
            if (temp == aa)
            {
                c = mid;
                break;
            }
            else if (temp < aa)
            {
                if (mid > c)
                {
                    c = mid;
                }
                left = mid + BigInteger::one();
            }
            else
            {
                right = mid - BigInteger::one();
            }
        }
    }
    return c;
}

/**
 * Let n be the digit number of the big integer a,
 * let m be the digit number of the big integer b,
 * the time complexity is about O(log(n) * m * n),
 * which equals to the divide operation.
 * @param a Big integer a.
 * @param b Big integer b.
 * @return The operate result.
 */
BigInteger operator %(const BigInteger &a, const BigInteger &b)
{
    BigInteger c = a.absolute() - a.absolute() / b.absolute() * b.absolute();
    if (a._positive != b._positive)
    {
        c._positive = false;
    }
    return c;
}

BigInteger BigInteger::gcd(const BigInteger a, const BigInteger b)
{
    if (b == BigInteger::zero())
    {
        return a;
    }
    return gcd(b, a % b);
}

void BigInteger::clearLeadingZero()
{
    for (int i = this->_data.size() - 1; i > 0; --i)
    {
        if (this->_data.at(i) == 0)
        {
            this->_data.pop_back();
        }
        else
        {
            break;
        }
    }
}

QString BigInteger::toString() const
{
    QString str = "";
    if ((*this) == zero())
    {
        str = "0";
    }
    else
    {
        if (!this->_positive)
        {
            str = "-";
        }
        str += QString("%1").arg(this->_data.at(this->_data.size() - 1));
        for (int i = this->_data.size() - 2; i >= 0; --i)
        {
            if (this->_data.at(i) < 10)
            {
                str += "000";
            }
            else if (this->_data.at(i) < 100)
            {
                str += "00";
            }
            else if (this->_data.at(i) < 1000)
            {
                str += "0";
            }
            str += QString("%1").arg(this->_data.at(i));
        }
    }
    return str;
}

void BigInteger::print() const
{
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << this->toString();
    out.flush();
}

void BigInteger::printLine() const
{
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << this->toString() << endl;
    out.flush();
}

void BigInteger::printDebug() const
{
    QTextStream out(stdout, QIODevice::WriteOnly);
    if (this->_positive)
    {
        out << "+";
    }
    else
    {
        out << "-";
    }
    out << "(" <<this->_data.size() << ")";
    for (int i = 0; i < this->_data.size(); ++i)
    {
        out << " " << this->_data.at(i);
    }
    out << endl;
    out.flush();
}

void BigInteger::printAll() const
{
    this->print();
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << " | ";
    out.flush();
    this->printDebug();
}
