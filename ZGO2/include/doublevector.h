#ifndef DOUBLEVECTOR_H
#define DOUBLEVECTOR_H
/**
 * 用于double型计算的向量。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class DoubleVector
{
public:
    DoubleVector();
    virtual ~DoubleVector();
    int length() const;
    void setLength(const int len);
    bool isVector() const;
    void setIsVector(const bool value);
    double getValue(const int pos = 0) const;
    void setValue(const int pos, const double value);
    void setValue(const double value);
    void setAll(const double value);

    static DoubleVector One(int len);
    static DoubleVector Zero(int len);
    static DoubleVector Exp(const DoubleVector &a);

    friend DoubleVector operator +(const DoubleVector &a, const DoubleVector &b);
    friend DoubleVector operator -(const DoubleVector &a, const DoubleVector &b);
    friend DoubleVector operator *(const DoubleVector &a, const DoubleVector &b);
    friend DoubleVector operator /(const DoubleVector &a, const DoubleVector &b);

protected:
    bool _isVector;
    QVector<double> _values;
};

#endif // DOUBLEVECTOR_H
