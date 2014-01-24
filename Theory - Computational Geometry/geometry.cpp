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

Point operator -(const Point &a, const Point &b)
{
    Point c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

struct Line
{
    double a, b, c;
};

struct Segment
{
    Point u, v;
    Line line() const
    {
        Line line;
        line.a = u.y - v.y;
        line.b = v.x - u.x;
        line.c = u.x * v.y - v.x * u.y;
        return line;
    }
};

double dist(const Point &a, const Point &b)
{
    return (a - b).norm();
}

double dist(const Point &point, const Line &line)
{
    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b);
}

bool isIntersect(const Point &point ,const Line &line)
{
    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0;
}

double dist(const Point &point, const Segment &segment)
{
    return max(min(dist(point, segment.u), dist(point, segment.v)), dist(point, segment.line()));
}

bool isIntersect(const Point &point ,const Segment &segment)
{
    if (isIntersect(point, segment.line()))
    {
        if (dblcmp(segment.u.y - segment.v.y) == 0)
        {
            return point.x > min(segment.u.x, segment.v.x) && point.x < max(segment.u.x, segment.v.x);
        }
        return point.y > min(segment.u.y, segment.v.y) && point.y < max(segment.u.y, segment.v.y);
    }
    return false;
}

int main()
{
    return 0;
}
