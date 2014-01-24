#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;
const double PI = acos(-1.0);

int dblcmp(double x)
{
    if (fabs(x) < EPS)
    {
        return 0;
    }
    return x > 0 ? 1 : -1;
}

struct Point
{
    double x, y;
    inline double norm() const
    {
        return sqrt(x * x + y * y);
    }
};

Point operator +(const Point &a, const Point &b)
{
    Point c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Point operator -(const Point &a, const Point &b)
{
    Point c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

double operator *(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

double operator ^(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

bool operator ==(const Point &a, const Point &b)
{
    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0;
}

double dist(const Point &a, const Point &b)
{
    return (a - b).norm();
}

double cross(const Point &a, const Point &b, const Point &o)
{
    return (a - o) ^ (b - o);
}

struct Segment
{
    Point u, v;
};

bool inIntersect(const Segment &a, const Segment &b)
{
    return dblcmp(cross(a.u, a.v, b.u)) * dblcmp(cross(a.u, a.v, b.v)) <= 0 &&
        dblcmp(cross(b.u, b.v, a.u)) * dblcmp(cross(b.u, b.v, a.v)) <= 0;
}

Point intersectPoint(const Segment &a, const Segment &b)
{
    double area1 = cross(b.u, b.v, a.u);
    double area2 = cross(b.u, b.v, a.v);
    double area = area1 + area2;
    double scale = area1 / area;
    Point c;
    c.x = a.u.x + (b.u.x - a.u.x) * scale;
    c.y = a.u.y + (b.u.y - a.u.y) * scale;
    return c;
}

int main()
{
    return 0;
}
