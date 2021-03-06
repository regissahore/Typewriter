/**
 * 连接两个引脚的连线的结构，由一组有顺序的坐标表示。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include <vector>

class Wire
{
public:
    Wire();
    virtual ~Wire();
    void add(const double x, const double y);
    void remove(unsigned int index);
    int count() const;
    void set(const unsigned int index, const double x, const double y);
    double x(const unsigned int index) const;
    double y(const unsigned int index) const;
    void setU(const int u);
    void setV(const int v);
    int u() const;
    int v() const;
    double length() const;
    double length(const unsigned int index) const;
    CPoint getSegmentPoint(double seg) const;

private:
    std::vector<double> _x;
    std::vector<double> _y;
    int _u;
    int _v;
};

