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
    Point()
    {
        x = 0.0;
        y = 0.0;
    }
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    inline void input()
    {
        scanf("%lf%lf", &x, &y);
    }
    inline void output()
    {
        printf("%.3lf %.3lf\n", x, y);
    }
    inline double norm()
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

double angle(const Point &a, const Point &b)
{
    return atan2(b.y - a.y, b.x - a.x);
}

double angle(const Point &a, const Point &b, const Point &o)
{
    return angle(b, o) - angle(a, o);
}

struct Line
{
    double a, b, c;
    inline void input()
    {
        scanf("%lf %lf %lf", &a, &b, &c);
    }
    inline void output()
    {
        printf("%.3lf %.3lf %.3lf\n", a, b, c);
    }
};

struct Segment
{
    Point u, v;
    inline void input()
    {
        u.input();
        v.input();
    }
    inline void output()
    {
        printf("%.3lf %.3lf %.3lf %.3lf\n", u.x, u.y, v.x, v.y);
    }
    Line line()
    {
        Line line;
        line.a = u.y - v.y;
        line.b = v.x - u.x;
        line.c = u.x * v.y - v.x * u.y;
        return line;
    }
    double length()
    {
        return dist(u, v);
    }
};

struct Triangle
{
    Point a;
    Point b;
    Point c;
};

struct Rectangle
{
    double x, y;
    double w, h;
};

struct Polygon
{
    vector<Point> vertex;
};

struct Circle
{
    double x, y;
    double radius;
};

int main()
{
    return 0;
}
