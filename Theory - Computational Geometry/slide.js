desc = [];
show = [];
code = [];

desc.push(function() {
    header("二维结构的定义");
});
show.push(function(context) {
    var point1 = Point();
    var point2 = Point();
    var point3 = Point();
    var segment = Segment();
    var line = Line();
    var polygon = Polygon();
    var rectangle = Rectangle();
    var circle = Circle();
    drawAxis(context);
    point1.x = 1.0;
    point1.y = 2.0;
    drawPoint(context, point1);
    point1.x = 2.0;
    point1.y = 2.0;
    point2.x = 4.5;
    point2.y = 6.5;
    segment.u = point1;
    segment.v = point2;
    drawSegment(context, segment);
    line.a = 1;
    line.b = 2;
    line.c = 3;
    drawLine(context, line);
    point1.x = -8.0;
    point1.y = -8.0;
    point2.x = -6.0;
    point2.y = -6.0;
    point3.x = -7.0;
    point3.y = -4.0;
    polygon.vertex.push(point1);
    polygon.vertex.push(point2);
    polygon.vertex.push(point3);
    drawPolygon(context, polygon);
    rectangle.x = -4.0;
    rectangle.y = -5.0;
    rectangle.width = 6.0;
    rectangle.height = 2.7;
    drawRectangle(context, rectangle);
    circle.x = -5.0;
    circle.y = 6.0;
    circle.radius = 2.0;
    drawCircle(context, circle);
});
code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \n \nstruct Point \n{ \n    double x, y; \n}; \n \nstruct Segment \n{ \n    Point u, v; \n}; \n \nstruct Line \n{ \n    double a, b, c; \n}; \n \nstruct Triangle \n{ \n    Point a; \n    Point b; \n    Point c; \n}; \n \nstruct Rectangle \n{ \n    double x, y; \n    double w, h; \n}; \n \nstruct Polygon \n{ \n    vector<Point> vertex; \n}; \n \nstruct Circle \n{ \n    double x, y; \n    double radius; \n}; \n \nint main() \n{ \n    Point point; \n    point.x = 1.0; \n    point.y = 2.0; \n    Segment segment; \n    segment.u.x = 2.0; \n    segment.u.y = 2.0; \n    segment.v.x = 4.5; \n    segment.v.y = 6.5; \n    Line line; \n    line.a = 1.0; \n    line.b = 2.0; \n    line.c = 3.0; \n    Triangle triangle; \n    triangle.a.x = -8.0; \n    triangle.a.y = -8.0; \n    triangle.b.x = -6.0; \n    triangle.b.y = -6.0; \n    triangle.c.x = -7.0; \n    triangle.c.y = -4.0; \n    Rectangle rectangle; \n    rectangle.x = -4.0; \n    rectangle.y = -5.0; \n    rectangle.w = 6.0; \n    rectangle.h = 2.7; \n    Circle circle; \n    circle.x = -5; \n    circle.y = 6; \n    circle.radius = 2; \n    return 0; \n} \n");

desc.push(function() {
    header("点与点的关系");
});

show.push(function(context) {
    drawAxis(context);
    var point1 = Point();
    var point2 = Point();
    var point3 = Point();
    point1.x = 2.0;
    point1.y = 4.0;
    point2.x = 6.0;
    point2.y = 5.0;
    point3.x = 1.0;
    point3.y = 2.0;
    var segment1 = Segment();
    var segment2 = Segment();
    segment1.u = point1;
    segment1.v = point3;
    segment2.u = point2;
    segment2.v = point3;
    drawSegment(context, segment1);
    drawSegment(context, segment2);
    drawPoint(context, point1);
    drawPoint(context, point2);
    drawPoint(context, point3);
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    Point() \n    { \n        x = 0.0; \n        y = 0.0; \n    } \n    Point(double x, double y) \n    { \n        this->x = x; \n        this->y = y; \n    } \n    inline void input() \n    { \n        scanf(\"%lf%lf\", &x, &y); \n    } \n    inline void output() \n    { \n        printf(\"%.3lf %.3lf\\n\", x, y); \n    } \n    inline double norm() \n    { \n        return sqrt(x * x + y * y); \n    } \n}; \n \nPoint operator +(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x + b.x; \n    c.y = a.y + b.y; \n    return c; \n} \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \nbool operator ==(const Point &a, const Point &b) \n{ \n    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0; \n} \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).norm(); \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \ndouble angle(const Point &a, const Point &b) \n{ \n    return atan2(b.y - a.y, b.x - a.x); \n} \n \ndouble angle(const Point &a, const Point &b, const Point &o) \n{ \n    return angle(b, o) - angle(a, o); \n} \n \nint main() \n{ \n    Point point1(1.0, 2.0); \n    Point point2(3.0, 2.0); \n    Point point3(1.0, 1.0); \n    printf(\"%lf %lf %lf\\n\", point1 * point2, cross(point1, point2, point3), angle(point1, point2, point3)); \n    return 0; \n} \n");

window.onload = function() {
    setContent(desc, show, code);
}
