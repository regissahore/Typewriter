#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    Point() \n    { \n        x = 0.0; \n        y = 0.0; \n    } \n    Point(double x, double y) \n    { \n        this->x = x; \n        this->y = y; \n    } \n    inline void input() \n    { \n        scanf(\"%lf%lf\", &x, &y); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf\\n\", x, y); \n    } \n    inline double length() const \n    { \n        return sqrt(x * x + y * y); \n    } \n    inline Point norm() const \n    { \n        Point norm; \n        norm.x = x / length(); \n        norm.y = y / length(); \n        return norm; \n    } \n}; \n \nPoint operator +(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x + b.x; \n    c.y = a.y + b.y; \n    return c; \n} \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \nPoint operator *(const Point &a, const double b) \n{ \n    Point c; \n    c.x = a.x * b; \n    c.y = a.y * b; \n    return c; \n} \n \nPoint operator /(const Point &a, const double b) \n{ \n    Point c; \n    c.x = a.x / b; \n    c.y = a.y / b; \n    return c; \n} \n \nbool operator ==(const Point &a, const Point &b) \n{ \n    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0; \n} \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).length(); \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \ndouble angle(const Point &a, const Point &b) \n{ \n    return atan2(b.y - a.y, b.x - a.x); \n} \n \ndouble angle(const Point &a, const Point &b, const Point &o) \n{ \n    return angle(b, o) - angle(a, o); \n} \n \nstruct Line \n{ \n    double a, b, c; \n    Line() \n    { \n        a = b = c = 0.0; \n    } \n    Line(double a, double b, double c) \n    { \n        this->a = a; \n        this->b = b; \n        this->c = c; \n    } \n    inline void input() \n    { \n        scanf(\"%lf %lf %lf\", &a, &b, &c); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf %.3lf\\n\", a, b, c); \n    } \n}; \n \ndouble dist(const Point &point, const Line &line) \n{ \n    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b); \n} \n \nbool isIntersect(const Point &point ,const Line &line) \n{ \n    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0; \n} \n \n \nbool isParallel(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b - a.b * b.a) == 0; \n} \n \nbool isVertical(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b + a.b * b.a) == 0; \n} \n \nPoint intersectPoint(const Line &a, const Line &b) \n{ \n    double a1 = a.a, b1 = a.b, c1 = a.c; \n    double a2 = b.a, b2 = b.b, c2 = b.c; \n    Point c; \n    c.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1); \n    c.y = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1); \n    return c; \n} \n \nstruct Segment \n{ \n    Point u, v; \n    Segment() \n    { \n    } \n    Segment(double x1, double y1, double x2, double y2) \n    { \n        u.x = x1; \n        u.y = y1; \n        v.x = x2; \n        v.y = y2; \n    } \n    Segment(const Point &u, const Point &v) \n    { \n        this->u = u; \n        this->v = v; \n    } \n    inline void input() \n    { \n        u.input(); \n        v.input(); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf %.3lf %.3lf\\n\", u.x, u.y, v.x, v.y); \n    } \n    Line line() const \n    { \n        Line line; \n        line.a = u.y - v.y; \n        line.b = v.x - u.x; \n        line.c = u.x * v.y - v.x * u.y; \n        return line; \n    } \n    Line perpendicularBisector() const \n    { \n        Segment bisector; \n        bisector.u = (u + v) * 0.5; \n        bisector.v.x = bisector.u.x + (u.y - v.y); \n        bisector.v.y = bisector.u.y - (u.x - v.x); \n        return bisector.line(); \n    } \n    double length() const \n    { \n        return dist(u, v); \n    } \n}; \n \ndouble dist(const Point &point, const Segment &segment) \n{ \n    return max(min(dist(point, segment.u), dist(point, segment.v)), dist(point, segment.line())); \n} \n \nbool isIntersect(const Point &point ,const Segment &segment) \n{ \n    if (isIntersect(point, segment.line())) \n    { \n        if (dblcmp(segment.u.y - segment.v.y) == 0) \n        { \n            return point.x > min(segment.u.x, segment.v.x) && point.x < max(segment.u.x, segment.v.x); \n        } \n        return point.y > min(segment.u.y, segment.v.y) && point.y < max(segment.u.y, segment.v.y); \n    } \n    return false; \n} \n \nbool inIntersect(const Segment &a, const Segment &b) \n{ \n    return dblcmp(cross(a.u, a.v, b.u)) * dblcmp(cross(a.u, a.v, b.v)) <= 0 && \n        dblcmp(cross(b.u, b.v, a.u)) * dblcmp(cross(b.u, b.v, a.v)) <= 0; \n} \n \nPoint intersectPoint(const Segment &a, const Segment &b) \n{ \n    double area1 = fabs(cross(b.u, b.v, a.u)); \n    double area2 = fabs(cross(b.u, b.v, a.v)); \n    double area = area1 + area2; \n    double scale = area1 / area; \n    Point c; \n    c.x = a.u.x + (a.v.x - a.u.x) * scale; \n    c.y = a.u.y + (a.v.y - a.u.y) * scale; \n    return c; \n} \n \nstruct Triangle \n{ \n    Point a; \n    Point b; \n    Point c; \n    Triangle() \n    { \n    } \n    Triangle(double x1, double y1, double x2, double y2, double x3, double y3) \n    { \n        a.x = x1; \n        a.y = y1; \n        b.x = x2; \n        b.y = y2; \n        c.x = x3; \n        c.y = y3; \n    } \n    Triangle(const Point &a, const Point &b, const Point &c) \n    { \n        this->a = a; \n        this->b = b; \n        this->c = c; \n    } \n    inline void input() \n    { \n        a.input(); \n        b.input(); \n        c.input(); \n    } \n    inline void output() const \n    { \n        a.output(); \n        b.output(); \n        c.output(); \n    } \n    double area() const \n    { \n        return fabs(cross(a, b, c)) * 0.5; \n    } \n    Line medianA() const \n    { \n        return Segment(a, (b + c) * 0.5).line(); \n    } \n    Line medianB() const \n    { \n        return Segment(b, (a + c) * 0.5).line(); \n    } \n    Line medianC() const \n    { \n        return Segment(c, (a + b) * 0.5).line(); \n    } \n    Point centroid() const \n    { \n        return intersectPoint(medianA(), medianB()); \n    } \n    Line altitudeA() const \n    { \n        Segment altitude; \n        altitude.u = a; \n        altitude.v.x = altitude.u.x + (b.y - c.y); \n        altitude.v.y = altitude.u.y - (b.x - c.x); \n        return altitude.line(); \n    } \n    Line altitudeB() const \n    { \n        Segment altitude; \n        altitude.u = b; \n        altitude.v.x = altitude.u.x + (a.y - c.y); \n        altitude.v.y = altitude.u.y - (a.x - c.x); \n        return altitude.line(); \n    } \n    Line altitudeC() const \n    { \n        Segment altitude; \n        altitude.u = c; \n        altitude.v.x = altitude.u.x + (a.y - b.y); \n        altitude.v.y = altitude.u.y - (a.x - b.x); \n        return altitude.line(); \n    } \n    Point orthoCenter() const \n    { \n        return intersectPoint(altitudeA(), altitudeB()); \n    } \n    Line perpendicularBisectorA() const \n    { \n        return Segment(b, c).perpendicularBisector(); \n    } \n    Line perpendicularBisectorB() const \n    { \n        return Segment(a, c).perpendicularBisector(); \n    } \n    Line perpendicularBisectorC() const \n    { \n        return Segment(a, b).perpendicularBisector(); \n    } \n    Point circumCenter() const \n    { \n        return intersectPoint(perpendicularBisectorA(), perpendicularBisectorB()); \n    } \n    double circumscribedCircleRadius() const \n    { \n        double la = (b - c).length(); \n        double lb = (a - c).length(); \n        double lc = (a - b).length(); \n        return la * lb * lc / sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc)); \n    } \n    Line angleBisectorA() const \n    { \n        Segment bisector; \n        bisector.u = a; \n        bisector.v = bisector.u + ((b - a).norm() + (c - a).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Line angleBisectorB() const \n    { \n        Segment bisector; \n        bisector.u = b; \n        bisector.v = bisector.u + ((a - b).norm() + (c - b).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Line angleBisectorC() const \n    { \n        Segment bisector; \n        bisector.u = c; \n        bisector.v = bisector.u + ((a - c).norm() + (b - c).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Point inCircle() const \n    { \n        return intersectPoint(angleBisectorA(), angleBisectorB()); \n    } \n    double inscribedCircleRaidus() const \n    { \n        double la = (b - c).length(); \n        double lb = (a - c).length(); \n        double lc = (a - b).length(); \n        return sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc)) / (la + lb + lc) * 0.5; \n    } \n}; \n \ndouble triangleArea(double la, double lb, double lc) \n{ \n    double p = (la + lb + lc) * 0.5; \n    return sqrt(p * (p - la) * (p - lb) * (p - lc)); \n} \n \nint main() \n{ \n    Triangle triangle1(-8, 5, -4, 3, -5, 9); \n    triangle1.medianA().output(); \n    triangle1.medianB().output(); \n    triangle1.medianC().output(); \n    triangle1.centroid().output(); \n    Triangle triangle2(8, 5, 4, 3, 5, 9); \n    triangle2.altitudeA().output(); \n    triangle2.altitudeB().output(); \n    triangle2.altitudeC().output(); \n    triangle2.orthoCenter().output(); \n    Triangle triangle3(-8, -5, -4, -3, -5, -9); \n    triangle3.perpendicularBisectorA().output(); \n    triangle3.perpendicularBisectorB().output(); \n    triangle3.perpendicularBisectorC().output(); \n    triangle3.circumCenter().output(); \n    printf(\"%lf\\n\", triangle3.circumscribedCircleRadius()); \n    Triangle triangle4(8, -5, 4, -3, 5, -9); \n    triangle4.angleBisectorA().output(); \n    triangle4.angleBisectorB().output(); \n    triangle4.angleBisectorC().output(); \n    triangle4.inCircle().output(); \n    printf(\"%lf\\n\", triangle4.inscribedCircleRaidus()); \n    return 0; \n} \n