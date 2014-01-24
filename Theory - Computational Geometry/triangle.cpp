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
    inline void output() const
    {
        printf("%.3lf %.3lf\n", x, y);
    }
    inline double length() const
    {
        return sqrt(x * x + y * y);
    }
    inline Point norm() const
    {
        Point norm;
        norm.x = x / length();
        norm.y = y / length();
        return norm;
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

Point operator *(const Point &a, const double b)
{
    Point c;
    c.x = a.x * b;
    c.y = a.y * b;
    return c;
}

Point operator /(const Point &a, const double b)
{
    Point c;
    c.x = a.x / b;
    c.y = a.y / b;
    return c;
}

bool operator ==(const Point &a, const Point &b)
{
    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0;
}

double dist(const Point &a, const Point &b)
{
    return (a - b).length();
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
    inline void input()
    {
        scanf("%lf %lf %lf", &a, &b, &c);
    }
    inline void output() const
    {
        printf("%.3lf %.3lf %.3lf\n", a, b, c);
    }
};

double dist(const Point &point, const Line &line)
{
    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b);
}

bool isIntersect(const Point &point ,const Line &line)
{
    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0;
}


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

struct Segment
{
    Point u, v;
    Segment()
    {
    }
    Segment(double x1, double y1, double x2, double y2)
    {
        u.x = x1;
        u.y = y1;
        v.x = x2;
        v.y = y2;
    }
    Segment(const Point &u, const Point &v)
    {
        this->u = u;
        this->v = v;
    }
    inline void input()
    {
        u.input();
        v.input();
    }
    inline void output() const
    {
        printf("%.3lf %.3lf %.3lf %.3lf\n", u.x, u.y, v.x, v.y);
    }
    Line line() const
    {
        Line line;
        line.a = u.y - v.y;
        line.b = v.x - u.x;
        line.c = u.x * v.y - v.x * u.y;
        return line;
    }
    Line perpendicularBisector() const
    {
        Segment bisector;
        bisector.u = (u + v) * 0.5;
        bisector.v.x = bisector.u.x + (u.y - v.y);
        bisector.v.y = bisector.u.y - (u.x - v.x);
        return bisector.line();
    }
    double length() const
    {
        return dist(u, v);
    }
};

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

bool inIntersect(const Segment &a, const Segment &b)
{
    return dblcmp(cross(a.u, a.v, b.u)) * dblcmp(cross(a.u, a.v, b.v)) <= 0 &&
        dblcmp(cross(b.u, b.v, a.u)) * dblcmp(cross(b.u, b.v, a.v)) <= 0;
}

Point intersectPoint(const Segment &a, const Segment &b)
{
    double area1 = fabs(cross(b.u, b.v, a.u));
    double area2 = fabs(cross(b.u, b.v, a.v));
    double area = area1 + area2;
    double scale = area1 / area;
    Point c;
    c.x = a.u.x + (a.v.x - a.u.x) * scale;
    c.y = a.u.y + (a.v.y - a.u.y) * scale;
    return c;
}

struct Triangle
{
    Point a;
    Point b;
    Point c;
    Triangle()
    {
    }
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        a.x = x1;
        a.y = y1;
        b.x = x2;
        b.y = y2;
        c.x = x3;
        c.y = y3;
    }
    Triangle(const Point &a, const Point &b, const Point &c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    inline void input()
    {
        a.input();
        b.input();
        c.input();
    }
    inline void output() const
    {
        a.output();
        b.output();
        c.output();
    }
    double area() const
    {
        return fabs(cross(a, b, c)) * 0.5;
    }
    Line medianA() const
    {
        return Segment(a, (b + c) * 0.5).line();
    }
    Line medianB() const
    {
        return Segment(b, (a + c) * 0.5).line();
    }
    Line medianC() const
    {
        return Segment(c, (a + b) * 0.5).line();
    }
    Point centroid() const
    {
        return intersectPoint(medianA(), medianB());
    }
    Line altitudeA() const
    {
        Segment altitude;
        altitude.u = a;
        altitude.v.x = altitude.u.x + (b.y - c.y);
        altitude.v.y = altitude.u.y - (b.x - c.x);
        return altitude.line();
    }
    Line altitudeB() const
    {
        Segment altitude;
        altitude.u = b;
        altitude.v.x = altitude.u.x + (a.y - c.y);
        altitude.v.y = altitude.u.y - (a.x - c.x);
        return altitude.line();
    }
    Line altitudeC() const
    {
        Segment altitude;
        altitude.u = c;
        altitude.v.x = altitude.u.x + (a.y - b.y);
        altitude.v.y = altitude.u.y - (a.x - b.x);
        return altitude.line();
    }
    Point orthoCenter() const
    {
        return intersectPoint(altitudeA(), altitudeB());
    }
    Line perpendicularBisectorA() const
    {
        return Segment(b, c).perpendicularBisector();
    }
    Line perpendicularBisectorB() const
    {
        return Segment(a, c).perpendicularBisector();
    }
    Line perpendicularBisectorC() const
    {
        return Segment(a, b).perpendicularBisector();
    }
    Point circumCenter() const
    {
        return intersectPoint(perpendicularBisectorA(), perpendicularBisectorB());
    }
    double circumscribedCircleRadius() const
    {
        double la = (b - c).length();
        double lb = (a - c).length();
        double lc = (a - b).length();
        return la * lb * lc / sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc));
    }
    Line angleBisectorA() const
    {
        Segment bisector;
        bisector.u = a;
        bisector.v = bisector.u + ((b - a).norm() + (c - a).norm()) * 0.5;
        return bisector.line();
    }
    Line angleBisectorB() const
    {
        Segment bisector;
        bisector.u = b;
        bisector.v = bisector.u + ((a - b).norm() + (c - b).norm()) * 0.5;
        return bisector.line();
    }
    Line angleBisectorC() const
    {
        Segment bisector;
        bisector.u = c;
        bisector.v = bisector.u + ((a - c).norm() + (b - c).norm()) * 0.5;
        return bisector.line();
    }
    Point inCircle() const
    {
        return intersectPoint(angleBisectorA(), angleBisectorB());
    }
    double inscribedCircleRaidus() const
    {
        double la = (b - c).length();
        double lb = (a - c).length();
        double lc = (a - b).length();
        return sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc)) / (la + lb + lc) * 0.5;
    }
};

double triangleArea(double la, double lb, double lc)
{
    double p = (la + lb + lc) * 0.5;
    return sqrt(p * (p - la) * (p - lb) * (p - lc));
}

int main()
{
    Triangle triangle1(-8, 5, -4, 3, -5, 9);
    triangle1.medianA().output();
    triangle1.medianB().output();
    triangle1.medianC().output();
    triangle1.centroid().output();
    Triangle triangle2(8, 5, 4, 3, 5, 9);
    triangle2.altitudeA().output();
    triangle2.altitudeB().output();
    triangle2.altitudeC().output();
    triangle2.orthoCenter().output();
    Triangle triangle3(-8, -5, -4, -3, -5, -9);
    triangle3.perpendicularBisectorA().output();
    triangle3.perpendicularBisectorB().output();
    triangle3.perpendicularBisectorC().output();
    triangle3.circumCenter().output();
    printf("%lf\n", triangle3.circumscribedCircleRadius());
    Triangle triangle4(8, -5, 4, -3, 5, -9);
    triangle4.angleBisectorA().output();
    triangle4.angleBisectorB().output();
    triangle4.angleBisectorC().output();
    triangle4.inCircle().output();
    printf("%lf\n", triangle4.inscribedCircleRaidus());
    return 0;
}
