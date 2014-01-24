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
    inline void output() const
    {
        printf("%.3lf %.3lf\n", x, y);
    }
};

struct Line
{
    double a, b, c;
    Line()
    {
        a = b = c = 0.0;
    }
    Line(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

bool isParallel(const Line &a, const Line &b)
{
    return dblcmp(a.a * b.b - a.b * b.a) == 0;
}

bool isVertical(const Line &a, const Line &b)
{
    return dblcmp(a.a * b.b + a.b * b.a) == 0;
}

Point intersectPoint(const Line &a, const Line &b)
{
    double a1 = a.a, b1 = a.b, c1 = a.c;
    double a2 = b.a, b2 = b.b, c2 = b.c;
    Point c;
    c.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    c.y = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    return c;
}

int main()
{
    Line line1(1, 2, 3);
    Line line2(-2, 1, 3);
    intersectPoint(line1, line2).output();
    return 0;
}
