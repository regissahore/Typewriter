#ifndef BIGINTEGER_H
#define BIGINTEGER_H
/**
 * The unlimited big integer.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class QString;

class BigInteger
{
public:
    BigInteger();
    virtual ~BigInteger();
    static BigInteger valueOf(int value);
    static BigInteger valueOf(QString value);
    static BigInteger zero();
    static BigInteger one();
    int digitNum() const;
    bool positive() const;
    BigInteger copy() const;
    BigInteger opposite() const;
    BigInteger absolute() const;
    BigInteger half() const;
    friend bool operator ==(const BigInteger &a, const BigInteger &b);
    friend bool operator !=(const BigInteger &a, const BigInteger &b);
    friend bool operator <(const BigInteger &a, const BigInteger &b);
    friend bool operator >(const BigInteger &a, const BigInteger &b);
    friend bool operator <=(const BigInteger &a, const BigInteger &b);
    friend bool operator >=(const BigInteger &a, const BigInteger &b);
    friend BigInteger operator +(const BigInteger &a, const BigInteger &b);
    friend BigInteger operator -(const BigInteger &a, const BigInteger &b);
    friend BigInteger operator *(const BigInteger &a, const BigInteger &b);
    friend BigInteger operator /(const BigInteger &a, const BigInteger &b);
    friend BigInteger operator %(const BigInteger &a, const BigInteger &b);
    static BigInteger gcd(const BigInteger a, const BigInteger b);
    void clearLeadingZero();
    void removeEnd();
    QString toString() const;
    void print() const;
    void printLine() const;
    void printDebug() const;
    void printAll() const;

protected:
    QVector<int> _data;
    bool _positive;
};

#endif // BIGINTEGER_H
