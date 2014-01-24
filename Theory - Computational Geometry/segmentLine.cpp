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
};

struct Line
{
    double a, b, c;
    inline void output()
    {
        printf("%.3lf %.3lf %.3lf\n", a, b, c);
    }
};

struct Segment
{
    Point u, v;
    Line line()
    {
        Line line;
        line.a = u.y - v.y;
        line.b = v.x - u.x;
        line.c = u.x * v.y - v.x * u.y;
        return line;
    }
};

int main()
{
    Segment segment;
    segment.u.x = 5.0;
    segment.u.y = 4.0;
    segment.v.x = 4.0;
    segment.v.y = 5.0;
    segment.line().output();
    segment.u.x = -3.0;
    segment.u.y = -4.0;
    segment.v.x = -3.0;
    segment.v.y = 4.0;
    segment.line().output();
    segment.u.x = -3.0;
    segment.u.y = -4.0;
    segment.v.x = 3.0;
    segment.v.y = -4.0;
    segment.line().output();
    return 0;
}
