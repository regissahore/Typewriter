#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H
/**
 * The unlimited big decimal.
 * Actually it is a fraction.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "biginteger.h"

class QString;

class BigDecimal
{
public:
    BigDecimal();
    virtual ~BigDecimal();
    static BigDecimal valueOf(int numerator, int denominator);
    static BigDecimal valueOf(double value);
    static BigDecimal valueOf(QString value);
    static BigDecimal zero();
    static BigDecimal one();
    BigInteger numerator() const;
    BigInteger denominator() const;
    bool positive() const;
    BigDecimal copy() const;
    BigDecimal opposite() const;
    BigDecimal absolute() const;
    friend bool operator ==(const BigDecimal &a, const BigDecimal &b);
    friend bool operator <(const BigDecimal &a, const BigDecimal &b);
    friend bool operator >(const BigDecimal &a, const BigDecimal &b);
    friend bool operator <=(const BigDecimal &a, const BigDecimal &b);
    friend bool operator >=(const BigDecimal &a, const BigDecimal &b);
    friend BigDecimal operator +(const BigDecimal &a, const BigDecimal &b);
    friend BigDecimal operator -(const BigDecimal &a, const BigDecimal &b);
    friend BigDecimal operator *(const BigDecimal &a, const BigDecimal &b);
    friend BigDecimal operator /(const BigDecimal &a, const BigDecimal &b);
    QString toString() const;
    void print() const;
    void printLine() const;
    void printDebug() const;
    void printAll() const;

protected:
    BigInteger _numerator;
    BigInteger _denominator;
    void reduce();
};

#endif // BIGDECIMAL_H
