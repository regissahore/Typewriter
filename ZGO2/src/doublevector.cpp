#include <cstdio>
#include <algorithm>
#include <qmath.h>
#include <QString>
#include "doublevector.h"
using namespace std;

/**
 * 默认的头为0号操作符。
 */
DoubleVector::Head::Node::Node()
{
    this->id = 0;
    this->index = 1;
}

DoubleVector::Head::Node::Node(int id, int index)
{
    this->id = id;
    this->index = index;
}

bool operator ==(const DoubleVector::Head::Node &a, const DoubleVector::Head::Node &b)
{
    return a.id == b.id && a.index == b.index;
}

bool operator !=(const DoubleVector::Head::Node &a, const DoubleVector::Head::Node &b)
{
    return a.id != b.id || a.index != b.index;
}

bool operator <(const DoubleVector::Head::Node &a, const DoubleVector::Head::Node &b)
{
    if (a.id == b.id)
    {
        return a.index < b.index;
    }
    return a.id < b.id;
}

bool operator >(const DoubleVector::Head::Node &a, const DoubleVector::Head::Node &b)
{
    return b < a;
}

DoubleVector::Head::Head()
{
}

void DoubleVector::Head::addNode(int id, int index)
{
    DoubleVector::Head::Node node(id, index);
    for (int i = 0; i < this->list.size(); ++i)
    {
        if (this->list[i] == node)
        {
            return;
        }
    }
    this->list.push_back(node);
}

bool operator ==(const DoubleVector::Head &a, const DoubleVector::Head &b)
{
    if (a.list.size() != b.list.size())
    {
        return false;
    }
    for (int i = 0; i < a.list.size(); ++i)
    {
        if (a.list[i] != b.list[i])
        {
            return false;
        }
    }
    return true;
}

bool operator <(const DoubleVector::Head &a, const DoubleVector::Head &b)
{
    int len = min(a.list.size(), b.list.size());
    for (int i = 0; i < len; ++i)
    {
        if (a.list[i] < b.list[i])
        {
            return true;
        }
        else if (a.list[i] > b.list[i])
        {
            return false;
        }
    }
    return a.list.size() == len && b.list.size() != len;
}

DoubleVector::Head operator +(const DoubleVector::Head &a, const DoubleVector::Head &b)
{
    set<DoubleVector::Head::Node> nodeSet;
    for (int i = 0; i < a.list.size(); ++i)
    {
        nodeSet.insert(a.list[i]);
    }
    for (int i = 0; i < b.list.size(); ++i)
    {
        nodeSet.insert(b.list[i]);
    }
    DoubleVector::Head head;
    for (set<DoubleVector::Head::Node>::iterator it = nodeSet.begin(); it != nodeSet.end(); ++it)
    {
        DoubleVector::Head::Node node = *it;
        head.list.push_back(node);
    }
    return head;
}

DoubleVector::DoubleVector()
{
    this->setIsVector(false);
    this->_values.push_back(0.0);
    this->_head.push_back(DoubleVector::Head());
}

DoubleVector::DoubleVector(const double value)
{
    this->setIsVector(false);
    this->_values.push_back(value);
    this->_head.push_back(DoubleVector::Head());
}

DoubleVector::~DoubleVector()
{
    this->_values.clear();
    this->_head.clear();
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
            this->_head.push_back(DoubleVector::Head());
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
                this->_head.pop_back();
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
        if (pos >= 0)
        {
            this->_values[0] = value;
        }
    }
}

double DoubleVector::getValue(const Head head)
{
    for (int i = 0; i < this->_values.size(); ++i)
    {
        if (this->_head[i] == head)
        {
            return this->_values[i];
        }
    }
    return 0.0;
}

void DoubleVector::setValue(const DoubleVector::Head head, const double value)
{
    for (int i = 0; i < this->_values.size(); ++i)
    {
        if (this->_head[i] == head)
        {
            this->_values[i] = value;
            break;
        }
    }
}

void DoubleVector::addHead(const int pos, const int id, const int index)
{
    this->_head[pos].addNode(id, index);
}

void DoubleVector::setAll(const double value)
{
    for (int i = 0; i < this->length(); ++i)
    {
        this->setValue(i, value);
    }
}

QString DoubleVector::toString(int index)
{
    return QString::number(this->getValue(index), 'f', 10);
}

QString DoubleVector::toNameString(int index)
{
    QString res = "";
    if (index < 0 || index >= this->_head.size())
    {
        return "";
    }
    if (this->_head[index].list.size() > 0)
    {
        res += "[";
        for (int i = 0; i < this->_head[index].list.size(); ++i)
        {
            if (i)
            {
                res += "_";
            }
            res += QString("%1[%2]").arg(this->_head[index].list[i].id).arg(this->_head[index].list[i].index + 1);
        }
        res += "] ";
    }
    return res;
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
        b._head[i] = a._head[i];
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
        b._head[i] = a._head[i];
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
        this->_values[i] = c._values[i];
        this->_head[i] = c._head[i];
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
        this->_values[i] = c._values[i];
        this->_head[i] = c._head[i];
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
        this->_values[i] = c._values[i];
        this->_head[i] = c._head[i];
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
        this->_values[i] = c._values[i];
        this->_head[i] = c._head[i];
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
        b._head[i] = a._head[i];
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
    bool flag = false;
    if (a.length() == b.length())
    {
        flag = true;
        for (int i = 0; i < a.length(); ++i)
        {
            if (!(a._head[i] == b._head[i]))
            {
                flag = false;
                break;
            }
        }
    }

    if (flag)
    {
        DoubleVector c = DoubleVector::Zero(a.length());
        for (int i = 0; i < a.length(); ++i)
        {
            c.setValue(i, a.getValue(i) + b.getValue(i));
            c._head[i] = a._head[i];
        }
        return c;
    }

    set<DoubleVector::Head> headSet;
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            headSet.insert(a._head[i] + b._head[j]);
        }
    }
    QVector<DoubleVector::Head> headList;
    for (set<DoubleVector::Head>::iterator it = headSet.begin(); it != headSet.end(); ++it)
    {
        headList.push_back(*it);
    }
    DoubleVector c = DoubleVector::Zero(headList.size());
    for (int i = 0; i < headList.size(); ++i)
    {
        c._head[i] = headList[i];
    }
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            DoubleVector::Head head = a._head[i] + b._head[j];
            c.setValue(head, c.getValue(head) + (a.getValue(i) + b.getValue(j)));
        }
    }
    return c;
}

DoubleVector operator -(const DoubleVector &a, const DoubleVector &b)
{
    bool flag = false;
    if (a.length() == b.length())
    {
        flag = true;
        for (int i = 0; i < a.length(); ++i)
        {
            if (!(a._head[i] == b._head[i]))
            {
                flag = false;
                break;
            }
        }
    }

    if (flag)
    {
        DoubleVector c = DoubleVector::Zero(a.length());
        for (int i = 0; i < a.length(); ++i)
        {
            c.setValue(i, a.getValue(i) - b.getValue(i));
            c._head[i] = a._head[i];
        }
        return c;
    }

    set<DoubleVector::Head> headSet;
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            headSet.insert(a._head[i] + b._head[j]);
        }
    }
    QVector<DoubleVector::Head> headList;
    for (set<DoubleVector::Head>::iterator it = headSet.begin(); it != headSet.end(); ++it)
    {
        headList.push_back(*it);
    }
    DoubleVector c = DoubleVector::Zero(headList.size());
    for (int i = 0; i < headList.size(); ++i)
    {
        c._head[i] = headList[i];
    }
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            DoubleVector::Head head = a._head[i] + b._head[j];
            c.setValue(head, c.getValue(head) + (a.getValue(i) - b.getValue(j)));
        }
    }
    return c;
}

DoubleVector operator *(const DoubleVector &a, const DoubleVector &b)
{
    bool flag = false;
    if (a.length() == b.length())
    {
        flag = true;
        for (int i = 0; i < a.length(); ++i)
        {
            if (!(a._head[i] == b._head[i]))
            {
                flag = false;
                break;
            }
        }
    }

    if (flag)
    {
        DoubleVector c = DoubleVector::Zero(a.length());
        for (int i = 0; i < a.length(); ++i)
        {
            c.setValue(i, a.getValue(i) * b.getValue(i));
            c._head[i] = a._head[i];
        }
        return c;
    }

    set<DoubleVector::Head> headSet;
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            headSet.insert(a._head[i] + b._head[j]);
        }
    }
    QVector<DoubleVector::Head> headList;
    for (set<DoubleVector::Head>::iterator it = headSet.begin(); it != headSet.end(); ++it)
    {
        headList.push_back(*it);
    }
    DoubleVector c = DoubleVector::Zero(headList.size());
    for (int i = 0; i < headList.size(); ++i)
    {
        c._head[i] = headList[i];
    }
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            DoubleVector::Head head = a._head[i] + b._head[j];
            c.setValue(head, c.getValue(head) + (a.getValue(i) * b.getValue(j)));
        }
    }
    return c;
}

DoubleVector operator /(const DoubleVector &a, const DoubleVector &b)
{
    bool flag = false;
    if (a.length() == b.length())
    {
        flag = true;
        for (int i = 0; i < a.length(); ++i)
        {
            if (!(a._head[i] == b._head[i]))
            {
                flag = false;
                break;
            }
        }
    }

    if (flag)
    {
        DoubleVector c = DoubleVector::Zero(a.length());
        for (int i = 0; i < a.length(); ++i)
        {
            c.setValue(i, a.getValue(i) / b.getValue(i));
            c._head[i] = a._head[i];
        }
        return c;
    }

    set<DoubleVector::Head> headSet;
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            headSet.insert(a._head[i] + b._head[j]);
        }
    }
    QVector<DoubleVector::Head> headList;
    for (set<DoubleVector::Head>::iterator it = headSet.begin(); it != headSet.end(); ++it)
    {
        headList.push_back(*it);
    }
    DoubleVector c = DoubleVector::Zero(headList.size());
    for (int i = 0; i < headList.size(); ++i)
    {
        c._head[i] = headList[i];
    }
    for (int i = 0; i < a._head.size(); ++i)
    {
        for (int j = 0; j < b._head.size(); ++j)
        {
            DoubleVector::Head head = a._head[i] + b._head[j];
            c.setValue(head, c.getValue(head) + (a.getValue(i) / b.getValue(j)));
        }
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
        c._head[i] = a._head[i];
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
        c._head[i] = a._head[i];
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
        c._head[i] = a._head[i];
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
        c._head[i] = a._head[i];
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
        c._head[i] = b._head[i];
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
        c._head[i] = b._head[i];
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
        c._head[i] = b._head[i];
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
        c._head[i] = b._head[i];
    }
    return c;
}
