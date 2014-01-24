head = [];
desc = [];
show = [];
code = [];

head.push("二维结构的定义");

desc.push([
"常用的二维结构包括点、线段、直线、三角形、矩形、多边形和圆。",
"大部分时候我们都可以用double来表示位置，但对于某些题目来说，double可能会有精度问题，这时也可以选用long long。",
"实际中，我们这里的三角形定义用得并不多。"
]);

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

head.push("点与点的关系");

desc.push([
"点的结构和向量相同，这里直接用点表示向量。",
"由于使用double，不能使用==进行比较，通常当数字差距小于EPS这个阈值时，我们认为两个数相等。",
"向量的乘法有点乘和叉乘两种，点乘可以用于角度的计算，而叉乘可以用于面积和方位的计算。"
]);

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

head.push("线段转化为直线");

desc.push([
"由于直线到线段是一个信息量增加的过程，所以我们一般不会遇到这种情况。",
"将直线a、b、c三个参数同时乘上非零的实数，它所表达的直线并没有发生改变。",
"我们将线段的两点带入到直线的方程中，得到两个三元一次方程，有无数组解，所以我们可以在避免除法的基础上构造一个解。",
"a = y1 - y2",
"b = x2 - x1",
"c = x1 × y2 - x2 × y1"
]);

show.push(function(context) {
    drawAxis(context);
    var segment = Segment();
    var line = Line();
    line.a = -1.0;
    line.b = -1.0;
    line.c = 9.0;
    drawLine(context, line);
    segment.u.x = 5.0;
    segment.u.y = 4.0;
    segment.v.x = 4.0;
    segment.v.y = 5.0;
    drawSegment(context, segment);
    drawPoint(context, segment.u);
    drawPoint(context, segment.v);
    line.a = -8.0;
    line.b = 0.0;
    line.c = -24.0;
    drawLine(context, line);
    segment.u.x = -3.0;
    segment.u.y = -4.0;
    segment.v.x = -3.0;
    segment.v.y = 4.0;
    drawSegment(context, segment);
    drawPoint(context, segment.u);
    drawPoint(context, segment.v);
    line.a = 0.0;
    line.b = 6.0;
    line.c = 24.0;
    drawLine(context, line);
    segment.u.x = -3.0;
    segment.u.y = -4.0;
    segment.v.x = 3.0;
    segment.v.y = -4.0;
    drawSegment(context, segment);
    drawPoint(context, segment.u);
    drawPoint(context, segment.v);
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n}; \n \nstruct Line \n{ \n    double a, b, c; \n    inline void output() \n    { \n        printf(\"%.3lf %.3lf %.3lf\\n\", a, b, c); \n    } \n}; \n \nstruct Segment \n{ \n    Point u, v; \n    Line line() \n    { \n        Line line; \n        line.a = u.y - v.y; \n        line.b = v.x - u.x; \n        line.c = u.x * v.y - v.x * u.y; \n        return line; \n    } \n}; \n \nint main() \n{ \n    Segment segment; \n    segment.u.x = 5.0; \n    segment.u.y = 4.0; \n    segment.v.x = 4.0; \n    segment.v.y = 5.0; \n    segment.line().output(); \n    segment.u.x = -3.0; \n    segment.u.y = -4.0; \n    segment.v.x = -3.0; \n    segment.v.y = 4.0; \n    segment.line().output(); \n    segment.u.x = -3.0; \n    segment.u.y = -4.0; \n    segment.v.x = 3.0; \n    segment.v.y = -4.0; \n    segment.line().output(); \n    return 0; \n} \n");

head.push("点与直线的关系");

desc.push([
"点与直线的关系有在直线上和在直线外两种，把点代入直线方程结果为0则在直线上。结果的正负表示着点相对于直线的方向。",
"点与直线的距离直接套公式算即可。"
]);

show.push(function() {
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n}; \n \nstruct Line \n{ \n    double a, b, c; \n}; \n \ndouble dist(const Point &point, const Line &line) \n{ \n    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b); \n} \n \nbool isIntersect(const Point &point ,const Line &line) \n{ \n    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0; \n} \n \nint main() \n{ \n    return 0; \n} \n");

head.push("点与线段的关系");

desc.push([
"点与线段的关系首先可以分为点在线段上和点在线段外。",
"线段的结构也可以看做为一条射线，对于点在线段外的情况，还分为点在线段左侧、点在线段右侧、点在线段的延长线上的情况。",
"点在线段左右侧可以用叉乘进行判断，在计算几何中经常使用。",
"点到线段的距离要考虑垂线是否在线段上。"
]);

show.push(function() {});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    inline double norm() const \n    { \n        return sqrt(x * x + y * y); \n    } \n}; \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \nstruct Line \n{ \n    double a, b, c; \n}; \n \nstruct Segment \n{ \n    Point u, v; \n    Line line() const \n    { \n        Line line; \n        line.a = u.y - v.y; \n        line.b = v.x - u.x; \n        line.c = u.x * v.y - v.x * u.y; \n        return line; \n    } \n}; \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).norm(); \n} \n \ndouble dist(const Point &point, const Line &line) \n{ \n    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b); \n} \n \nbool isIntersect(const Point &point ,const Line &line) \n{ \n    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0; \n} \n \ndouble dist(const Point &point, const Segment &segment) \n{ \n    return max(min(dist(point, segment.u), dist(point, segment.v)), dist(point, segment.line())); \n} \n \nbool isIntersect(const Point &point ,const Segment &segment) \n{ \n    if (isIntersect(point, segment.line())) \n    { \n        if (dblcmp(segment.u.y - segment.v.y) == 0) \n        { \n            return point.x > min(segment.u.x, segment.v.x) && point.x < max(segment.u.x, segment.v.x); \n        } \n        return point.y > min(segment.u.y, segment.v.y) && point.y < max(segment.u.y, segment.v.y); \n    } \n    return false; \n} \n \nint main() \n{ \n    return 0; \n} \n");

head.push("线段与线段的关系");

desc.push([
"线段是否相交由叉乘来判定，如果每一个线段的两个端点都处于另一个线段所处直线的两边，则可以认为线段相交。",
"当一个线段的端点在另外一个线段上，如果认为这种情况也为相交，则这时的相交判定为严格相交。是否使用严格相交根据实际题目进行选择。",
"线段的交点用面积的比值获得。"
]);

show.push(function() {});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    inline double norm() const \n    { \n        return sqrt(x * x + y * y); \n    } \n}; \n \nPoint operator +(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x + b.x; \n    c.y = a.y + b.y; \n    return c; \n} \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \nbool operator ==(const Point &a, const Point &b) \n{ \n    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0; \n} \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).norm(); \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \nstruct Segment \n{ \n    Point u, v; \n}; \n \nbool inIntersect(const Segment &a, const Segment &b) \n{ \n    return dblcmp(cross(a.u, a.v, b.u)) * dblcmp(cross(a.u, a.v, b.v)) <= 0 && \n        dblcmp(cross(b.u, b.v, a.u)) * dblcmp(cross(b.u, b.v, a.v)) <= 0; \n} \n \nPoint intersectPoint(const Segment &a, const Segment &b) \n{ \n    double area1 = cross(b.u, b.v, a.u); \n    double area2 = cross(b.u, b.v, a.v); \n    double area = area1 + area2; \n    double scale = area1 / area; \n    Point c; \n    c.x = a.u.x + (b.u.x - a.u.x) * scale; \n    c.y = a.u.y + (b.u.y - a.u.y) * scale; \n    return c; \n} \n \nint main() \n{ \n    return 0; \n} \n");

window.onload = function() {
    setContent(head, desc, show, code);
}
