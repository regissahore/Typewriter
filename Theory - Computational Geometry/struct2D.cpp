#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Point
{
    double x, y;
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
    Point point;
    point.x = 1.0;
    point.y = 2.0;
    Segment segment;
    segment.u.x = 2.0;
    segment.u.y = 2.0;
    segment.v.x = 4.5;
    segment.v.y = 6.5;
    Line line;
    line.a = 1.0;
    line.b = 2.0;
    line.c = 3.0;
    Triangle triangle;
    triangle.a.x = -8.0;
    triangle.a.y = -8.0;
    triangle.b.x = -6.0;
    triangle.b.y = -6.0;
    triangle.c.x = -7.0;
    triangle.c.y = -4.0;
    Rectangle rectangle;
    rectangle.x = -4.0;
    rectangle.y = -5.0;
    rectangle.w = 6.0;
    rectangle.h = 2.7;
    Circle circle;
    circle.x = -5;
    circle.y = 6;
    circle.radius = 2;
    return 0;
}
