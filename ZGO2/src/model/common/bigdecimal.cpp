#include <QtDebug>
#include <QTextStream>
#include <QString>
#include "bigdecimal.h"

const int MAX_DECIMAL_NUM = 20;

/**
 * The value is set to 1 / 1 when initializing.
 */
BigDecimal::BigDecimal()
{
    this->_numerator = BigInteger::one();
    this->_denominator = BigInteger::one();
}

BigDecimal::~BigDecimal()
{
}

BigDecimal BigDecimal::valueOf(int numerator, int denominator)
{
    BigDecimal decimal;
    decimal._numerator = BigInteger::valueOf(numerator);
    decimal._denominator = BigInteger::valueOf(denominator);
    decimal.reduce();
    return decimal;
}

BigDecimal BigDecimal::valueOf(QString numerator, QString denominator)
{
    BigDecimal decimal;
    decimal._numerator = BigInteger::valueOf(numerator);
    decimal._denominator = BigInteger::valueOf(denominator);
    decimal.reduce();
    return decimal;
}

BigDecimal BigDecimal::valueOf(double value)
{
    return BigDecimal::valueOf(QString("%1").arg(value));
}

BigDecimal BigDecimal::valueOf(QString value)
{
    QString numerator = "0";
    QString denominator = "1";
    if (value.at(0).unicode() == '-')
    {
        numerator = "-0";
        value.right(value.length() - 1);
    }
    bool dot = false;
    for (int i = 0; i < value.length(); ++i)
    {
        if (value.at(i).unicode() >= '0' && value.at(i).unicode() <= '9')
        {
            numerator += value.at(i);
            if (dot)
            {
                denominator += "0";
            }
        }
        else if (value.at(i).unicode() == '.')
        {
            dot = true;
        }
    }
    BigDecimal decimal;
    decimal._numerator = BigInteger::valueOf(numerator);
    decimal._denominator = BigInteger::valueOf(denominator);
    decimal.reduce();
    return decimal;
}

BigDecimal BigDecimal::zero()
{
    return BigDecimal::valueOf(0, 1);
}

BigDecimal BigDecimal::one()
{
    return BigDecimal::valueOf(1, 1);
}

BigInteger BigDecimal::numerator() const
{
    return this->_numerator;
}

BigInteger BigDecimal::denominator() const
{
    return this->_denominator;
}

bool BigDecimal::positive() const
{
    return this->_denominator.positive() == this->_numerator.positive();
}

BigDecimal BigDecimal::copy() const
{
    return (*this);
}

BigDecimal BigDecimal::opposite() const
{
    BigDecimal decimal = this->copy();
    decimal._numerator = decimal._numerator.opposite();
    return decimal;
}

BigDecimal BigDecimal::absolute() const
{
    BigDecimal decimal = this->copy();
    decimal._numerator = decimal._numerator.absolute();
    decimal._denominator = decimal._denominator.absolute();
    return decimal;
}

bool operator ==(const BigDecimal &a, const BigDecimal &b)
{
    if (a._numerator == BigInteger::zero() && b._numerator == BigInteger::zero())
    {
        return true;
    }
    return a._numerator * b._denominator == a._denominator * b._numerator;
}

bool operator <(const BigDecimal &a, const BigDecimal &b)
{
    if (a._numerator == BigInteger::zero() && b._numerator == BigInteger::zero())
    {
        return false;
    }
    if (a.positive() && !b.positive())
    {
        return false;
    }
    if (!a.positive() && b.positive())
    {
        return true;
    }
    if (a.positive())
    {
        return a._numerator * b._denominator < a._denominator * b._numerator;
    }
    return a.opposite() > b.opposite();
}

bool operator >(const BigDecimal &a, const BigDecimal &b)
{
    return b < a;
}

bool operator <=(const BigDecimal &a, const BigDecimal &b)
{
    return a < b || a == b;
}

bool operator >=(const BigDecimal &a, const BigDecimal &b)
{
    return a > b || a == b;
}

BigDecimal operator +(const BigDecimal &a, const BigDecimal &b)
{
    BigDecimal c;
    c._numerator = a._numerator * b._denominator + a._denominator * b._numerator;
    c._denominator = a._denominator * b._denominator;
    c.reduce();
    return c;
}

BigDecimal operator -(const BigDecimal &a, const BigDecimal &b)
{
    BigDecimal c;
    c._numerator = a._numerator * b._denominator - a._denominator * b._numerator;
    c._denominator = a._denominator * b._denominator;
    c.reduce();
    return c;
}

BigDecimal operator *(const BigDecimal &a, const BigDecimal &b)
{
    BigDecimal c;
    c._numerator = a._numerator * b._numerator;
    c._denominator = a._denominator * b._denominator;
    c.reduce();
    return c;
}

BigDecimal operator /(const BigDecimal &a, const BigDecimal &b)
{
    BigDecimal c;
    c._numerator = a._numerator * b._denominator;
    c._denominator = a._denominator * b._numerator;
    c.reduce();
    return c;
}

QString BigDecimal::toString()
{
    this->_denominator.clearLeadingZero();
    this->_numerator.clearLeadingZero();
    if (this->_denominator == BigInteger::zero())
    {
        return "INF";
    }
    QString str = (this->numerator() / this->denominator()).toString() + ".";
    BigInteger num = (this->numerator() % this->denominator()).absolute();
    BigInteger den = this->denominator().absolute();
    for (int i = 0; i < MAX_DECIMAL_NUM; ++i)
    {
        if (num == BigInteger::zero())
        {
            break;
        }
        num = num * BigInteger::valueOf(10);
        str += (num / den).toString();
        num = num % den;
    }
    for (int i = str.length() - 1; i >= 0; --i)
    {
        if (str[i].unicode() != '0')
        {
            str = str.left(i + 1);
            break;
        }
    }
    if (str[str.length() - 1].unicode() == '.')
    {
        str = str.left(str.length() - 1);
    }
    return str;
}

void BigDecimal::print()
{
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << this->toString();
    out.flush();
}

void BigDecimal::printLine()
{
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << this->toString() << endl;
    out.flush();
}

void BigDecimal::printDebug()
{
    this->numerator().print();
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << "/";
    out.flush();
    this->denominator().printLine();
}

void BigDecimal::printAll()
{
    this->print();
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << " | ";
    out.flush();
    this->printDebug();
}

void BigDecimal::reduce()
{
    while (this->_numerator.digitNum() > 24 && this->_denominator.digitNum() > 24)
    {
        this->_numerator.removeEnd();
        this->_denominator.removeEnd();
    }
    /*BigInteger g = BigInteger::gcd(this->numerator().absolute(), this->denominator().absolute());
    if (g != BigInteger::one())
    {
        this->_numerator = this->_numerator / g;
        this->_denominator = this->_denominator / g;
    }*/
}
