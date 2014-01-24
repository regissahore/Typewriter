#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

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
};

struct Segment
{
    Point u, v;
};

struct Line
{
    double a, b, c;
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
