#ifndef DOUBLEVECTOR_H
#define DOUBLEVECTOR_H
#include <set>
#include <map>
#include "stable.h"

class DoubleVector
{
public:
    struct Head
    {
        struct Node
        {
            int id;
            int index;
            Node();
            Node(int id, int index);
            friend bool operator ==(const Node &a, const Node &b);
            friend bool operator !=(const Node &a, const Node &b);
            friend bool operator <(const Node &a, const Node &b);
            friend bool operator >(const Node &a, const Node &b);
        };

        Head();
        void addNode(int id, int index);
        friend bool operator ==(const Head &a, const Head &b);
        friend bool operator <(const Head &a, const Head &b);
        friend Head operator +(const Head &a, const Head &b);
        QVector<Node> list;
    };

    DoubleVector();
    DoubleVector(const double value);
    virtual ~DoubleVector();
    int length() const;
    void setLength(const int len);
    bool isVector() const;
    void setIsVector(const bool value);
    double getValue(const int pos) const;
    void setValue(const int pos, const double value);
    double getValue(const Head head);
    void setValue(const Head head, const double value);
    void addHead(const int pos, const int id, const int index);
    void setAll(const double value);

    QString toString(int index);
    QString toNameString(int index);

    static DoubleVector One(int len);
    static DoubleVector Zero(int len);
    static DoubleVector Exp(const DoubleVector &a);
    static DoubleVector Sqrt(const DoubleVector &a);

    DoubleVector& operator +=(const DoubleVector &a);
    DoubleVector& operator -=(const DoubleVector &a);
    DoubleVector& operator *=(const DoubleVector &a);
    DoubleVector& operator /=(const DoubleVector &a);

    DoubleVector& operator +=(const double &a);
    DoubleVector& operator -=(const double &a);
    DoubleVector& operator *=(const double &a);
    DoubleVector& operator /=(const double &a);

    friend DoubleVector operator -(const DoubleVector &a);

    friend bool operator <(const DoubleVector &a, const DoubleVector &b);
    friend bool operator <(const DoubleVector &a, const double b);
    friend bool operator <(const double a, const DoubleVector &b);
    friend bool operator >(const DoubleVector &a, const DoubleVector &b);
    friend bool operator >(const DoubleVector &a, const double b);
    friend bool operator >(const double a, const DoubleVector &b);

    friend DoubleVector operator +(const DoubleVector &a, const DoubleVector &b);
    friend DoubleVector operator -(const DoubleVector &a, const DoubleVector &b);
    friend DoubleVector operator *(const DoubleVector &a, const DoubleVector &b);
    friend DoubleVector operator /(const DoubleVector &a, const DoubleVector &b);

    friend DoubleVector operator +(const DoubleVector &a, const double b);
    friend DoubleVector operator -(const DoubleVector &a, const double b);
    friend DoubleVector operator *(const DoubleVector &a, const double b);
    friend DoubleVector operator /(const DoubleVector &a, const double b);

    friend DoubleVector operator +(const double a, const DoubleVector &b);
    friend DoubleVector operator -(const double a, const DoubleVector &b);
    friend DoubleVector operator *(const double a, const DoubleVector &b);
    friend DoubleVector operator /(const double a, const DoubleVector &b);

protected:
    bool _isVector;
    QVector<double> _values;
    QVector<Head> _head;
};

#endif // DOUBLEVECTOR_H
