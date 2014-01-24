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
};

double dist(const Point &point, const Line &line)
{
    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b);
}

bool isIntersect(const Point &point ,const Line &line)
{
    return dblcmp(line.a * point.x + line.b * point.y + line.c);
}

int main()
{
    return 0;
}
