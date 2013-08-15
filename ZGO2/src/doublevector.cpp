#include <algorithm>
#include <qmath.h>
#include "doublevector.h"
using namespace std;

DoubleVector::DoubleVector()
{
    this->setIsVector(false);
    this->_values.push_back(0.0);
}

DoubleVector::DoubleVector(const double value)
{
    this->setIsVector(false);
    this->_values.push_back(value);
}

DoubleVector::~DoubleVector()
{
    this->_values.clear();
}

int DoubleVector::length() const
{
    return this->_values.size();
}

void DoubleVector::setLength(const int len)
{
    if (len > this->length())
    {
        if (len > 1)
        {
            this->setIsVector(true);
        }
        for (int i = this->length(); i < len; ++i)
        {
            this->_values.push_back(0.0);
        }
    }
    else if (len < this->length())
    {
        if (len == 1)
        {
            this->setIsVector(false);
        }
        if (len > 0)
        {
            for (int i = this->length(); i > len; --i)
            {
                this->_values.pop_back();
            }
        }
    }
}

bool DoubleVector::isVector() const
{
    return this->_isVector;
}

void DoubleVector::setIsVector(const bool value)
{
    this->_isVector = value;
}

double DoubleVector::getValue(const int pos) const
{
    if (this->isVector())
    {
        if (pos < 0 || pos >= this->_values.size())
        {
            return 0.0;
        }
        return this->_values[pos];
    }
    if (pos < 0)
    {
        return 0.0;
    }
    return this->_values[0];
}

void DoubleVector::setValue(const int pos, const double value)
{
    if (this->isVector())
    {
        if (pos >= 0 && pos < this->_values.size())
        {
            this->_values[pos] = value;
        }
    }
    else
    {
        if (pos > 0)
        {
            this->_values[0] = value;
        }
    }
}

void DoubleVector::setAll(const double value)
{
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, value);
    }
}

DoubleVector DoubleVector::One(int len)
{
    DoubleVector v;
    v.setLength(len);
    v.setAll(1.0);
    return v;
}

DoubleVector DoubleVector::Zero(int len)
{
    DoubleVector v;
    v.setLength(len);
    v.setAll(0.0);
    return v;
}

DoubleVector DoubleVector::Exp(const DoubleVector &a)
{
    DoubleVector b;
    b.setIsVector(a.isVector());
    b.setLength(a.length());
    for (int i = 0; i < a.length(); ++i)
    {
        b.setValue(i, exp(a.getValue(i)));
    }
    return b;
}

DoubleVector DoubleVector::Sqrt(const DoubleVector &a)
{
    DoubleVector b;
    b.setIsVector(a.isVector());
    b.setLength(a.length());
    for (int i = 0; i < a.length(); ++i)
    {
        b.setValue(i, sqrt(a.getValue(i)));
    }
    return b;
}

DoubleVector& DoubleVector::operator +=(const DoubleVector &a)
{
    DoubleVector c = *this + a;
    this->setIsVector(c.isVector());
    this->setLength(c.length());
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, c.getValue(i));
    }
    return *this;
}

DoubleVector& DoubleVector::operator -=(const DoubleVector &a)
{
    DoubleVector c = *this - a;
    this->setIsVector(c.isVector());
    this->setLength(c.length());
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, c.getValue(i));
    }
    return *this;
}

DoubleVector& DoubleVector::operator *=(const DoubleVector &a)
{
    DoubleVector c = *this * a;
    this->setIsVector(c.isVector());
    this->setLength(c.length());
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, c.getValue(i));
    }
    return *this;
}

DoubleVector& DoubleVector::operator /=(const DoubleVector &a)
{
    DoubleVector c = *this / a;
    this->setIsVector(c.isVector());
    this->setLength(c.length());
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, c.getValue(i));
    }
    return *this;
}

DoubleVector& DoubleVector::operator +=(const double &a)
{
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, this->getValue(i) + a);
    }
    return *this;
}

DoubleVector& DoubleVector::operator -=(const double &a)
{
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, this->getValue(i) - a);
    }
    return *this;
}

DoubleVector& DoubleVector::operator *=(const double &a)
{
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, this->getValue(i) * a);
    }
    return *this;
}

DoubleVector& DoubleVector::operator /=(const double &a)
{
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, this->getValue(i) / a);
    }
    return *this;
}

DoubleVector operator -(const DoubleVector &a)
{
    DoubleVector b;
    b.setIsVector(a.isVector());
    b.setLength(a.length());
    for (int i = 0; i < a.length(); ++i)
    {
        b.setValue(i, - a.getValue(i));
    }
    return b;
}

bool operator <(const DoubleVector &a, const DoubleVector &b)
{
    return a.getValue(0) < b.getValue(0);
}

bool operator <(const DoubleVector &a, const double b)
{
    return a.getValue(0) < b;
}

bool operator <(const double a, const DoubleVector &b)
{
    return a < b.getValue(0);
}

bool operator >(const DoubleVector &a, const DoubleVector &b)
{
    return a.getValue(0) > b.getValue(0);
}

bool operator >(const DoubleVector &a, const double b)
{
    return a.getValue(0) > b;
}

bool operator >(const double a, const DoubleVector &b)
{
    return a > b.getValue(0);
}

DoubleVector operator +(const DoubleVector &a, const DoubleVector &b)
{
    DoubleVector c;
    int len = max(a.length(), b.length());
    c.setIsVector(a.isVector() || b.isVector());
    c.setLength(len);
    for (int i = 0; i < len; ++i)
    {
        c.setValue(i, a.getValue(i) + b.getValue(i));
    }
    return c;
}

DoubleVector operator -(const DoubleVector &a, const DoubleVector &b)
{
    DoubleVector c;
    int len = max(a.length(), b.length());
    c.setIsVector(a.isVector() || b.isVector());
    c.setLength(len);
    for (int i = 0; i < len; ++i)
    {
        c.setValue(i, a.getValue(i) - b.getValue(i));
    }
    return c;
}

DoubleVector operator *(const DoubleVector &a, const DoubleVector &b)
{
    DoubleVector c;
    int len = max(a.length(), b.length());
    c.setIsVector(a.isVector() || b.isVector());
    c.setLength(len);
    for (int i = 0; i < len; ++i)
    {
        c.setValue(i, a.getValue(i) * b.getValue(i));
    }
    return c;
}

DoubleVector operator /(const DoubleVector &a, const DoubleVector &b)
{
    DoubleVector c;
    int len = max(a.length(), b.length());
    c.setIsVector(a.isVector() || b.isVector());
    c.setLength(len);
    for (int i = 0; i < len; ++i)
    {
        c.setValue(i, a.getValue(i) / b.getValue(i));
    }
    return c;
}

DoubleVector operator +(const DoubleVector &a, const double b)
{
    DoubleVector c;
    c.setIsVector(a.isVector());
    c.setLength(a.length());
    for (int i = 0; i < a.length(); ++i)
    {
        c.setValue(i, a.getValue(i) + b);
    }
    return c;
}

DoubleVector operator -(const DoubleVector &a, const double b)
{
    DoubleVector c;
    c.setIsVector(a.isVector());
    c.setLength(a.length());
    for (int i = 0; i < a.length(); ++i)
    {
        c.setValue(i, a.getValue(i) - b);
    }
    return c;
}

DoubleVector operator *(const DoubleVector &a, const double b)
{
    DoubleVector c;
    c.setIsVector(a.isVector());
    c.setLength(a.length());
    for (int i = 0; i < a.length(); ++i)
    {
        c.setValue(i, a.getValue(i) * b);
    }
    return c;
}

DoubleVector operator /(const DoubleVector &a, const double b)
{
    DoubleVector c;
    c.setIsVector(a.isVector());
    c.setLength(a.length());
    for (int i = 0; i < a.length(); ++i)
    {
        c.setValue(i, a.getValue(i) / b);
    }
    return c;
}

DoubleVector operator +(const double a, const DoubleVector &b)
{
    DoubleVector c;
    c.setIsVector(b.isVector());
    c.setLength(b.length());
    for (int i = 0; i < b.length(); ++i)
    {
        c.setValue(i, a + b.getValue(i));
    }
    return c;
}

DoubleVector operator -(const double a, const DoubleVector &b)
{
    DoubleVector c;
    c.setIsVector(b.isVector());
    c.setLength(b.length());
    for (int i = 0; i < b.length(); ++i)
    {
        c.setValue(i, a - b.getValue(i));
    }
    return c;
}

DoubleVector operator *(const double a, const DoubleVector &b)
{
    DoubleVector c;
    c.setIsVector(b.isVector());
    c.setLength(b.length());
    for (int i = 0; i < b.length(); ++i)
    {
        c.setValue(i, a * b.getValue(i));
    }
    return c;
}

DoubleVector operator /(const double a, const DoubleVector &b)
{
    DoubleVector c;
    c.setIsVector(b.isVector());
    c.setLength(b.length());
    for (int i = 0; i < b.length(); ++i)
    {
        c.setValue(i, a / b.getValue(i));
    }
    return c;
}
