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

show.push(function(context) {
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n}; \n \nstruct Line \n{ \n    double a, b, c; \n}; \n \ndouble dist(const Point &point, const Line &line) \n{ \n    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b); \n} \n \nbool isIntersect(const Point &point ,const Line &line) \n{ \n    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0; \n} \n \nint main() \n{ \n    return 0; \n} \n");

head.push("点与线段的关系");

desc.push([
"点与线段的关系首先可以分为点在线段上和点在线段外。",
"线段的结构也可以看做为一条射线，对于点在线段外的情况，还分为点在线段左侧、点在线段右侧、点在线段的延长线上的情况。",
"点在线段左右侧可以用叉乘进行判断，在计算几何中经常使用。",
"点到线段的距离要考虑垂线是否在线段上。"
]);

show.push(function(context) {});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    inline double norm() const \n    { \n        return sqrt(x * x + y * y); \n    } \n}; \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \nstruct Line \n{ \n    double a, b, c; \n}; \n \nstruct Segment \n{ \n    Point u, v; \n    Line line() const \n    { \n        Line line; \n        line.a = u.y - v.y; \n        line.b = v.x - u.x; \n        line.c = u.x * v.y - v.x * u.y; \n        return line; \n    } \n}; \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).norm(); \n} \n \ndouble dist(const Point &point, const Line &line) \n{ \n    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b); \n} \n \nbool isIntersect(const Point &point ,const Line &line) \n{ \n    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0; \n} \n \ndouble dist(const Point &point, const Segment &segment) \n{ \n    return max(min(dist(point, segment.u), dist(point, segment.v)), dist(point, segment.line())); \n} \n \nbool isIntersect(const Point &point ,const Segment &segment) \n{ \n    if (isIntersect(point, segment.line())) \n    { \n        if (dblcmp(segment.u.y - segment.v.y) == 0) \n        { \n            return point.x > min(segment.u.x, segment.v.x) && point.x < max(segment.u.x, segment.v.x); \n        } \n        return point.y > min(segment.u.y, segment.v.y) && point.y < max(segment.u.y, segment.v.y); \n    } \n    return false; \n} \n \nint main() \n{ \n    return 0; \n} \n");

head.push("线段与线段的关系");

desc.push([
"线段是否相交由叉乘来判定，如果每一个线段的两个端点都处于另一个线段所处直线的两边，则可以认为线段相交。",
"为加快运算速度，线段相交可分为快速排斥实验和跨立实验两部分。",
"当一个线段的端点在另外一个线段上，如果认为这种情况也为相交，则这时的相交判定为严格相交。是否使用严格相交根据实际题目进行选择。",
"线段的交点用面积的比值获得。"
]);

show.push(function(context) {
    drawAxis(context);
    var point = Point();
    point.x = 1.41;
    point.y = -0.59;
    var segment1 = Segment();
    var segment2 = Segment();
    segment1.u.x = -6;
    segment1.u.y = -8;
    segment1.v.x = 9;
    segment1.v.y = 7;
    segment2.u.x = -4;
    segment2.u.y = 5;
    segment2.v.x = 8;
    segment2.v.y = -7.4;
    drawSegment(context, segment1);
    drawSegment(context, segment2);
    drawPoint(context, point);
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    inline double norm() const \n    { \n        return sqrt(x * x + y * y); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf\\n\", x, y); \n    } \n}; \n \nPoint operator +(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x + b.x; \n    c.y = a.y + b.y; \n    return c; \n} \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \nbool operator ==(const Point &a, const Point &b) \n{ \n    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0; \n} \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).norm(); \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \nstruct Segment \n{ \n    Point u, v; \n    Segment() \n    { \n    } \n    Segment(double x1, double y1, double x2, double y2) \n    { \n        u.x = x1; \n        u.y = y1; \n        v.x = x2; \n        v.y = y2; \n    } \n}; \n \nbool inIntersect(const Segment &a, const Segment &b) \n{ \n    return dblcmp(cross(a.u, a.v, b.u)) * dblcmp(cross(a.u, a.v, b.v)) <= 0 && \n        dblcmp(cross(b.u, b.v, a.u)) * dblcmp(cross(b.u, b.v, a.v)) <= 0; \n} \n \nPoint intersectPoint(const Segment &a, const Segment &b) \n{ \n    double area1 = fabs(cross(b.u, b.v, a.u)); \n    double area2 = fabs(cross(b.u, b.v, a.v)); \n    double area = area1 + area2; \n    double scale = area1 / area; \n    Point c; \n    c.x = a.u.x + (a.v.x - a.u.x) * scale; \n    c.y = a.u.y + (a.v.y - a.u.y) * scale; \n    return c; \n} \n \nint main() \n{ \n    Segment segment1(-6, -8, 9, 7); \n    Segment segment2(-4, 5, 8, -7.4); \n    intersectPoint(segment1, segment2).output(); \n    return 0; \n} \n");

head.push("直线与直线的关系");

desc.push([
"直线比线段要简单，当a和b成比例时，两直线平行。当a和b交叉相乘和为0时，两直线垂直",
"直线的交点可以直接求解析解，二元一次方程。",
"x = (b1*c2 - b2*c1)/(a1*b2 - a2*b1)",
"y = -(a1*c2 - a2*c1)/(a1*b2 - a2*b1)"
]);

show.push(function(context) {
    drawAxis(context);
    var point = Point();
    point.x = 0.6;
    point.y = -1.8;
    var line1 = Line();
    var line2 = Line();
    line1.a = 1;
    line1.b = 2;
    line1.c = 3;
    line2.a = -2;
    line2.b = 1;
    line2.c = 3;
    drawLine(context, line1);
    drawLine(context, line2);
    drawPoint(context, point);
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    inline double norm() const \n    { \n        return sqrt(x * x + y * y); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf\\n\", x, y); \n    } \n}; \n \nstruct Line \n{ \n    double a, b, c; \n    Line() \n    { \n        a = b = c = 0.0; \n    } \n    Line(double a, double b, double c) \n    { \n        this->a = a; \n        this->b = b; \n        this->c = c; \n    } \n}; \n \nbool isParallel(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b - a.b * b.a) == 0; \n} \n \nbool isVertical(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b + a.b * b.a) == 0; \n} \n \nPoint intersectPoint(const Line &a, const Line &b) \n{ \n    double a1 = a.a, b1 = a.b, c1 = a.c; \n    double a2 = b.a, b2 = b.b, c2 = b.c; \n    Point c; \n    c.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1); \n    c.y = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1); \n    return c; \n} \n \nint main() \n{ \n    Line line1(1, 2, 3); \n    Line line2(-2, 1, 3); \n    intersectPoint(line1, line2).output(); \n    return 0; \n} \n");

head.push("三角形的特殊点");

desc.push([
"重心（centroid）：中线（median）的交点。",
"垂心（orthocenter）：高（altitude）的交点。",
"外心（circumcenter）：垂直平分线（perpendicular bisector）的交点。",
"内心（incircle）：角平分线（angle bisector）的交点。",
"费马点（Fermat point）：到三边距离最小的点，可以用模拟退火求得。当有内角不小于120°时，该点即为费马点。否则以三边向外做正三角形，正三角形顶点与对面的顶点连线交于费马点。",
"三角形面积：S = 0.5 * a * b * sinC",
"三角形面积：叉乘的一半的绝对值",
"三角形面积：海伦公式 p = (a + b + c) / 2, S = sqrt(p * (p - a) * (p - b) * (p - c))",
"外切圆半径：R = abc / sqrt((a + b + c)(b + c - a)(a + c - b)(a + b - c))",
"内切圆半径：r = sqrt((a + b + c)(b + c - a)(a + c - b)(a + b - c)) / (2(a + b + c))"
]);

show.push(function(context) {
    drawAxis(context);
    var triangle = Triangle();
    var line = Line();
    var point = Point();
    var circle = Circle();
    
    triangle.a.x = -8;
    triangle.a.y = 5;
    triangle.b.x = -4;
    triangle.b.y = 3;
    triangle.c.x = -5;
    triangle.c.y = 9;
    drawTriangle(context, triangle);
    line.a = -1;
    line.b = 3.5;
    line.c = -25.5;
    drawLine(context, line);
    line.a = -4;
    line.b = -2.5;
    line.c = -8.5;
    drawLine(context, line);
    line.a = 5;
    line.b = -1;
    line.c = 34;
    drawLine(context, line);
    point.x = -5.667;
    point.y = 5.667;
    drawPoint(context, point);
    
    triangle.a.x = 8;
    triangle.a.y = 5;
    triangle.b.x = 4;
    triangle.b.y = 3;
    triangle.c.x = 5;
    triangle.c.y = 9;
    drawTriangle(context, triangle);
    line.a = -1;
    line.b = -6;
    line.c = 38;
    drawLine(context, line);
    line.a = 3;
    line.b = -4;
    line.c = 0;
    drawLine(context, line);
    line.a = 4;
    line.b = 2;
    line.c = -38;
    drawLine(context, line);
    point.x = 6.909;
    point.y = 5.182;
    drawPoint(context, point);
    
    triangle.a.x = -8;
    triangle.a.y = -5;
    triangle.b.x = -4;
    triangle.b.y = -3;
    triangle.c.x = -5;
    triangle.c.y = -9;
    drawTriangle(context, triangle);
    line.a = 1;
    line.b = 6;
    line.c = 40.5;
    drawLine(context, line);
    line.a = -3;
    line.b = 4;
    line.c = 8.5;
    drawLine(context, line);
    line.a = -4;
    line.b = -2;
    line.c = -32;
    drawLine(context, line);
    circle.x = -5.045;
    circle.y = -5.909;
    circle.radius = 3.091;
    drawCircle(context, circle);
    point.x = -5.045;
    point.y = -5.909;
    drawPoint(context, point);
    
    triangle.a.x = 8;
    triangle.a.y = -5;
    triangle.b.x = 4;
    triangle.b.y = -3;
    triangle.c.x = 5;
    triangle.c.y = -9;
    drawTriangle(context, triangle);
    line.a = 0.176;
    line.b = -0.747;
    line.c = -5.147;
    drawLine(context, line);
    line.a = 0.717;
    line.b = 0.529;
    line.c = -1.279;
    drawLine(context, line);
    line.a = -0.893;
    line.b = 0.218;
    line.c = 6.426;
    drawLine(context, line);
    circle.x = 5.852;
    circle.y = -5.507;
    circle.radius = 1.414;
    drawCircle(context, circle);
    point.x = 5.852;
    point.y = -5.507;
    drawPoint(context, point);
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    Point() \n    { \n        x = 0.0; \n        y = 0.0; \n    } \n    Point(double x, double y) \n    { \n        this->x = x; \n        this->y = y; \n    } \n    inline void input() \n    { \n        scanf(\"%lf%lf\", &x, &y); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf\\n\", x, y); \n    } \n    inline double length() const \n    { \n        return sqrt(x * x + y * y); \n    } \n    inline Point norm() const \n    { \n        Point norm; \n        norm.x = x / length(); \n        norm.y = y / length(); \n        return norm; \n    } \n}; \n \nPoint operator +(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x + b.x; \n    c.y = a.y + b.y; \n    return c; \n} \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \nPoint operator *(const Point &a, const double b) \n{ \n    Point c; \n    c.x = a.x * b; \n    c.y = a.y * b; \n    return c; \n} \n \nPoint operator /(const Point &a, const double b) \n{ \n    Point c; \n    c.x = a.x / b; \n    c.y = a.y / b; \n    return c; \n} \n \nbool operator ==(const Point &a, const Point &b) \n{ \n    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0; \n} \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).length(); \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \ndouble angle(const Point &a, const Point &b) \n{ \n    return atan2(b.y - a.y, b.x - a.x); \n} \n \ndouble angle(const Point &a, const Point &b, const Point &o) \n{ \n    return angle(b, o) - angle(a, o); \n} \n \nstruct Line \n{ \n    double a, b, c; \n    Line() \n    { \n        a = b = c = 0.0; \n    } \n    Line(double a, double b, double c) \n    { \n        this->a = a; \n        this->b = b; \n        this->c = c; \n    } \n    inline void input() \n    { \n        scanf(\"%lf %lf %lf\", &a, &b, &c); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf %.3lf\\n\", a, b, c); \n    } \n}; \n \ndouble dist(const Point &point, const Line &line) \n{ \n    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b); \n} \n \nbool isIntersect(const Point &point ,const Line &line) \n{ \n    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0; \n} \n \n \nbool isParallel(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b - a.b * b.a) == 0; \n} \n \nbool isVertical(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b + a.b * b.a) == 0; \n} \n \nPoint intersectPoint(const Line &a, const Line &b) \n{ \n    double a1 = a.a, b1 = a.b, c1 = a.c; \n    double a2 = b.a, b2 = b.b, c2 = b.c; \n    Point c; \n    c.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1); \n    c.y = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1); \n    return c; \n} \n \nstruct Segment \n{ \n    Point u, v; \n    Segment() \n    { \n    } \n    Segment(double x1, double y1, double x2, double y2) \n    { \n        u.x = x1; \n        u.y = y1; \n        v.x = x2; \n        v.y = y2; \n    } \n    Segment(const Point &u, const Point &v) \n    { \n        this->u = u; \n        this->v = v; \n    } \n    inline void input() \n    { \n        u.input(); \n        v.input(); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf %.3lf %.3lf\\n\", u.x, u.y, v.x, v.y); \n    } \n    Line line() const \n    { \n        Line line; \n        line.a = u.y - v.y; \n        line.b = v.x - u.x; \n        line.c = u.x * v.y - v.x * u.y; \n        return line; \n    } \n    Line perpendicularBisector() const \n    { \n        Segment bisector; \n        bisector.u = (u + v) * 0.5; \n        bisector.v.x = bisector.u.x + (u.y - v.y); \n        bisector.v.y = bisector.u.y - (u.x - v.x); \n        return bisector.line(); \n    } \n    double length() const \n    { \n        return dist(u, v); \n    } \n}; \n \ndouble dist(const Point &point, const Segment &segment) \n{ \n    return max(min(dist(point, segment.u), dist(point, segment.v)), dist(point, segment.line())); \n} \n \nbool isIntersect(const Point &point ,const Segment &segment) \n{ \n    if (isIntersect(point, segment.line())) \n    { \n        if (dblcmp(segment.u.y - segment.v.y) == 0) \n        { \n            return point.x > min(segment.u.x, segment.v.x) && point.x < max(segment.u.x, segment.v.x); \n        } \n        return point.y > min(segment.u.y, segment.v.y) && point.y < max(segment.u.y, segment.v.y); \n    } \n    return false; \n} \n \nbool inIntersect(const Segment &a, const Segment &b) \n{ \n    return dblcmp(cross(a.u, a.v, b.u)) * dblcmp(cross(a.u, a.v, b.v)) <= 0 && \n        dblcmp(cross(b.u, b.v, a.u)) * dblcmp(cross(b.u, b.v, a.v)) <= 0; \n} \n \nPoint intersectPoint(const Segment &a, const Segment &b) \n{ \n    double area1 = fabs(cross(b.u, b.v, a.u)); \n    double area2 = fabs(cross(b.u, b.v, a.v)); \n    double area = area1 + area2; \n    double scale = area1 / area; \n    Point c; \n    c.x = a.u.x + (a.v.x - a.u.x) * scale; \n    c.y = a.u.y + (a.v.y - a.u.y) * scale; \n    return c; \n} \n \nstruct Triangle \n{ \n    Point a; \n    Point b; \n    Point c; \n    Triangle() \n    { \n    } \n    Triangle(double x1, double y1, double x2, double y2, double x3, double y3) \n    { \n        a.x = x1; \n        a.y = y1; \n        b.x = x2; \n        b.y = y2; \n        c.x = x3; \n        c.y = y3; \n    } \n    Triangle(const Point &a, const Point &b, const Point &c) \n    { \n        this->a = a; \n        this->b = b; \n        this->c = c; \n    } \n    inline void input() \n    { \n        a.input(); \n        b.input(); \n        c.input(); \n    } \n    inline void output() const \n    { \n        a.output(); \n        b.output(); \n        c.output(); \n    } \n    double area() const \n    { \n        return fabs(cross(a, b, c)) * 0.5; \n    } \n    Line medianA() const \n    { \n        return Segment(a, (b + c) * 0.5).line(); \n    } \n    Line medianB() const \n    { \n        return Segment(b, (a + c) * 0.5).line(); \n    } \n    Line medianC() const \n    { \n        return Segment(c, (a + b) * 0.5).line(); \n    } \n    Point centroid() const \n    { \n        return intersectPoint(medianA(), medianB()); \n    } \n    Line altitudeA() const \n    { \n        Segment altitude; \n        altitude.u = a; \n        altitude.v.x = altitude.u.x + (b.y - c.y); \n        altitude.v.y = altitude.u.y - (b.x - c.x); \n        return altitude.line(); \n    } \n    Line altitudeB() const \n    { \n        Segment altitude; \n        altitude.u = b; \n        altitude.v.x = altitude.u.x + (a.y - c.y); \n        altitude.v.y = altitude.u.y - (a.x - c.x); \n        return altitude.line(); \n    } \n    Line altitudeC() const \n    { \n        Segment altitude; \n        altitude.u = c; \n        altitude.v.x = altitude.u.x + (a.y - b.y); \n        altitude.v.y = altitude.u.y - (a.x - b.x); \n        return altitude.line(); \n    } \n    Point orthoCenter() const \n    { \n        return intersectPoint(altitudeA(), altitudeB()); \n    } \n    Line perpendicularBisectorA() const \n    { \n        return Segment(b, c).perpendicularBisector(); \n    } \n    Line perpendicularBisectorB() const \n    { \n        return Segment(a, c).perpendicularBisector(); \n    } \n    Line perpendicularBisectorC() const \n    { \n        return Segment(a, b).perpendicularBisector(); \n    } \n    Point circumCenter() const \n    { \n        return intersectPoint(perpendicularBisectorA(), perpendicularBisectorB()); \n    } \n    double circumscribedCircleRadius() const \n    { \n        double la = (b - c).length(); \n        double lb = (a - c).length(); \n        double lc = (a - b).length(); \n        return la * lb * lc / sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc)); \n    } \n    Line angleBisectorA() const \n    { \n        Segment bisector; \n        bisector.u = a; \n        bisector.v = bisector.u + ((b - a).norm() + (c - a).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Line angleBisectorB() const \n    { \n        Segment bisector; \n        bisector.u = b; \n        bisector.v = bisector.u + ((a - b).norm() + (c - b).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Line angleBisectorC() const \n    { \n        Segment bisector; \n        bisector.u = c; \n        bisector.v = bisector.u + ((a - c).norm() + (b - c).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Point inCircle() const \n    { \n        return intersectPoint(angleBisectorA(), angleBisectorB()); \n    } \n    double inscribedCircleRaidus() const \n    { \n        double la = (b - c).length(); \n        double lb = (a - c).length(); \n        double lc = (a - b).length(); \n        return sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc)) / (la + lb + lc) * 0.5; \n    } \n}; \n \ndouble triangleArea(double la, double lb, double lc) \n{ \n    double p = (la + lb + lc) * 0.5; \n    return sqrt(p * (p - la) * (p - lb) * (p - lc)); \n} \n \nint main() \n{ \n    Triangle triangle1(-8, 5, -4, 3, -5, 9); \n    triangle1.medianA().output(); \n    triangle1.medianB().output(); \n    triangle1.medianC().output(); \n    triangle1.centroid().output(); \n    Triangle triangle2(8, 5, 4, 3, 5, 9); \n    triangle2.altitudeA().output(); \n    triangle2.altitudeB().output(); \n    triangle2.altitudeC().output(); \n    triangle2.orthoCenter().output(); \n    Triangle triangle3(-8, -5, -4, -3, -5, -9); \n    triangle3.perpendicularBisectorA().output(); \n    triangle3.perpendicularBisectorB().output(); \n    triangle3.perpendicularBisectorC().output(); \n    triangle3.circumCenter().output(); \n    printf(\"%lf\\n\", triangle3.circumscribedCircleRadius()); \n    Triangle triangle4(8, -5, 4, -3, 5, -9); \n    triangle4.angleBisectorA().output(); \n    triangle4.angleBisectorB().output(); \n    triangle4.angleBisectorC().output(); \n    triangle4.inCircle().output(); \n    printf(\"%lf\\n\", triangle4.inscribedCircleRaidus()); \n    return 0; \n} \n");

head.push("矩形与矩形的关系");

desc.push([
"矩形的关系包括包含和相交两种。",
"包含判断四个点是否都在另外一个矩形中。",
"相交判断边是否出现交叉。"
]);

show.push(function(context) {});

code.push("struct Rectangle \n{ \n    double x, y; \n    double w, h; \n    Rectangle() \n    { \n        x = y = w = h = 0.0; \n    } \n    Rectangle(double x, double y, double w, double h) \n    { \n        this->x = x; \n        this->y = y; \n        this->w = w; \n        this->h = h; \n    } \n    inline void input() \n    { \n        scanf(\"%lf%lf%lf%lf\", &x, &y, &w, &h); \n    } \n    inline void output() \n    { \n        printf(\"%.3lf %.3lf %.3lf %.3lf\", x, y, w, h); \n    } \n    double left() const \n    { \n        return x; \n    } \n    double right() const \n    { \n        return x + w; \n    } \n    double top() const \n    { \n        return y; \n    } \n    double bottom() const \n    { \n        return y + h; \n    } \n    Point leftTop() const \n    { \n        return Point(left(), top()); \n    } \n    Point rightTop() const \n    { \n        return Point(right(), top()); \n    } \n    Point leftBottom() const \n    { \n        return Point(left(), bottom()); \n    } \n    Point rightBottom() const \n    { \n        return Point(right(), bottom()); \n    } \n    Segment toSegment() const \n    { \n        return Segment(leftTop(), rightBottom()); \n    } \n}; \n");

head.push("圆与圆的关系");

desc.push([
"圆的关系包括相离、外切、相交、内切、包含五种，都用圆心距离与半径进行比较即可。"
]);

show.push(function(context) {});

code.push("struct Circle \n{ \n    Point o; \n    double radius; \n    Circle() \n    { \n        radius = 0.0; \n    } \n    Circle(double x, double y, double radius) \n    { \n        o.x = x; \n        o.y = y; \n        this->radius = radius; \n    } \n    Circle(const Point &o, double radius) \n    { \n        this->o = o; \n        this->radius = radius; \n    } \n    inline void input() \n    { \n        o.input(); \n        scanf(\"%lf\", &radius); \n    } \n    inline void output() \n    { \n        printf(\"%.3lf %.3lf %.3lf\\n\", o.x, o.y, radius); \n    } \n}; \n \ndouble dist(const Circle &a, const Circle &b) \n{ \n    return dist(a.o, b.o); \n} \n");

head.push("凸多边形");

desc.push([
"判断点是否在凸多边形内，如果凸多边形的点已经排序可以用叉乘的正负是否一致来判定，也可以判断点与凸多边形的边构成的三角形的面积和与凸多边形的面积是否相等。",
"凸多边形的面积可以划分为三角形求得。"
]);

show.push(function(context) {});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <stack> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n}; \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \nstruct Polygon \n{ \n    vector<Point> vertex; \n    double area() const \n    { \n        double area = 0.0; \n        for (size_t i = 2; i < vertex.size(); ++i) \n        { \n            area += fabs(cross(vertex[i], vertex[i - 1], vertex[0])); \n        } \n        return area * 0.5; \n    } \n}; \n \nint main() \n{ \n    return 0; \n} \n");

head.push("Graham凸包");

desc.push([
"直角坐标排序：利用直角坐标排序，按纵坐标由小到大排序，纵坐标相等的情况下按横坐标由小到大排序。",
"极角排序：选择纵坐标最小的情况下横坐标最小的点作为参考点进行极角排序。",
"每次添边，如果左转则压榨，否则出栈直至左转。",
"时间复杂度：O(nlogn)"
]);

show.push(function(context) {
    drawAxis(context);
    var points = Array();
    var point = Point();
    var segment = Segment();
    var polygon = Polygon();
    point.x = 1;
    point.y = 2;
    points.push(point);
    point = Point();
    point.x = 4;
    point.y = -4;
    points.push(point);
    point = Point();
    point.x = -5;
    point.y = 5;
    points.push(point);
    point = Point();
    point.x = -3;
    point.y = -8;
    points.push(point);
    point = Point();
    point.x = -2;
    point.y = -9;
    points.push(point);
    point = Point();
    point.x = 8;
    point.y = 2;
    points.push(point);
    point = Point();
    point.x = -9;
    point.y = -4;
    points.push(point);
    point = Point();
    point.x = 6;
    point.y = -6;
    points.push(point);
    point = Point();
    point.x = 4;
    point.y = -2;
    points.push(point);
    point = Point();
    point.x = 7;
    point.y = 7;
    points.push(point);
    point = Point();
    point.x = -1;
    point.y = 6;
    points.push(point);
    point = Point();
    point.x = -2;
    point.y = -9;
    polygon.vertex.push(point);
    point = Point();
    point.x = 6;
    point.y = -6;
    polygon.vertex.push(point);
    point = Point();
    point.x = 8;
    point.y = 2;
    polygon.vertex.push(point);
    point = Point();
    point.x = 7;
    point.y = 7;
    polygon.vertex.push(point);
    point = Point();
    point.x = -1;
    point.y = 6;
    polygon.vertex.push(point);
    point = Point();
    point.x = -5;
    point.y = 5;
    polygon.vertex.push(point);
    point = Point();
    point.x = -9;
    point.y = -4;
    polygon.vertex.push(point);
    point = Point();
    point.x = -2;
    point.y = -9;
    polygon.vertex.push(point);
    for (var i = 0; i < points.length; ++i) {
        segment.u.x = -2;
        segment.u.y = -9;
        segment.v.x = points[i].x;
        segment.v.y = points[i].y;
        drawSegment(context, segment);
    }
    drawPolygon(context, polygon);
    for (var i = 0; i < points.length; ++i) {
        drawPoint(context, points[i]);
    }
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <stack> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    Point() \n    { \n        x = 0.0; \n        y = 0.0; \n    } \n    Point(double x, double y) \n    { \n        this->x = x; \n        this->y = y; \n    } \n    inline void input() \n    { \n        scanf(\"%lf%lf\", &x, &y); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf\\n\", x, y); \n    } \n    bool operator <(const Point &point) const \n    { \n        if (y == point.y) \n        { \n            return x < point.x; \n        } \n        return y < point.y; \n    } \n}; \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \nstruct Polygon \n{ \n    vector<Point> vertex; \n    inline void output() \n    { \n        for (size_t i = 0; i < vertex.size(); ++i) \n        { \n            vertex[i].output(); \n        } \n    } \n}; \n \nvoid graham(vector<Point> &points, Polygon &convex) \n{ \n    convex.vertex.clear(); \n    sort(points.begin(), points.end()); \n    convex.vertex.push_back(points[0]); \n    convex.vertex.push_back(points[1]); \n    for (size_t i = 2; i < points.size(); ++i) \n    { \n        while (convex.vertex.size() >= 2) \n        { \n            if (dblcmp((points[i] - convex.vertex[convex.vertex.size() - 1]) ^ (convex.vertex[convex.vertex.size() - 1] - convex.vertex[convex.vertex.size() - 2])) <= 0) \n            { \n                break; \n            } \n            convex.vertex.pop_back(); \n        } \n        convex.vertex.push_back(points[i]); \n    } \n    convex.vertex.push_back(points[points.size() - 2]); \n    int top = convex.vertex.size(); \n    for (int i = points.size() - 3; i >= 0; --i) \n    { \n        while (convex.vertex.size() >= top) \n        { \n            if (dblcmp((points[i] - convex.vertex[convex.vertex.size() - 1]) ^ (convex.vertex[convex.vertex.size() - 1] - convex.vertex[convex.vertex.size() - 2])) <= 0) \n            { \n                break; \n            } \n            convex.vertex.pop_back(); \n        } \n        convex.vertex.push_back(points[i]); \n    } \n} \n \nint main() \n{ \n    vector<Point> points; \n    points.push_back(Point(1, 2)); \n    points.push_back(Point(4, -4)); \n    points.push_back(Point(-5, 5)); \n    points.push_back(Point(-3, -8)); \n    points.push_back(Point(-2, -9)); \n    points.push_back(Point(8, 2)); \n    points.push_back(Point(-9, -4)); \n    points.push_back(Point(6, -6)); \n    points.push_back(Point(4, -2)); \n    points.push_back(Point(7, 7)); \n    points.push_back(Point(-1, 6)); \n    Polygon polygon; \n    graham(points, polygon); \n    polygon.output(); \n    return 0; \n} \n");

head.push("旋转卡壳");

desc.push([
"主要用于求凸包的直径，两个不相交的凸包的最大距离和最小距离。",
"按逆时针枚举凸包上的边，每次找最远的点，由于最远点也在按逆时针旋转，所以不考虑凸包时间复杂度为O(n)。"
]);

show.push(function(context) {
    drawAxis(context);
    var points = Array();
    var point = Point();
    var polygon = Polygon();
    point = Point();
    point.x = -2;
    point.y = -9;
    points.push(point);
    polygon.vertex.push(point);
    point = Point();
    point.x = 6;
    point.y = -6;
    points.push(point);
    polygon.vertex.push(point);
    point = Point();
    point.x = 8;
    point.y = 2;
    points.push(point);
    polygon.vertex.push(point);
    point = Point();
    point.x = 7;
    point.y = 7;
    points.push(point);
    polygon.vertex.push(point);
    point = Point();
    point.x = -1;
    point.y = 6;
    points.push(point);
    polygon.vertex.push(point);
    point = Point();
    point.x = -5;
    point.y = 5;
    points.push(point);
    polygon.vertex.push(point);
    point = Point();
    point.x = -9;
    point.y = -4;
    points.push(point);
    polygon.vertex.push(point);
    point = Point();
    point.x = -2;
    point.y = -9;
    points.push(point);
    polygon.vertex.push(point);
    drawPolygon(context, polygon);
    drawPolygon(context, polygon);
    for (var i = 0; i < points.length; ++i) {
        drawPoint(context, points[i]);
    }
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <stack> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    Point() \n    { \n        x = 0.0; \n        y = 0.0; \n    } \n    Point(double x, double y) \n    { \n        this->x = x; \n        this->y = y; \n    } \n    inline double length() const \n    { \n        return sqrt(x * x + y * y); \n    } \n}; \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).length(); \n} \n \ndouble rotatingCalipers(vector<Point> &points) \n{ \n    double ans = 0.0; \n    points.push_back(points[0]); \n    for (int i = 0, j = 1; i < points.size(); ++i) \n    { \n        while (fabs(cross(points[i], points[i + 1], points[j + 1])) > \n               fabs(cross(points[i], points[i + 1], points[j]))) \n        { \n            j = (j + 1) % (points.size() - 1); \n        } \n        ans = max(ans, max(dist(points[i], points[j]), dist(points[i + 1], points[j]))); \n    } \n    return ans; \n} \n \nint main() \n{ \n    vector<Point> points; \n    points.push_back(Point(-2, -9)); \n    points.push_back(Point(6, -6)); \n    points.push_back(Point(8, 2)); \n    points.push_back(Point(7, 7)); \n    points.push_back(Point(-1, 6)); \n    points.push_back(Point(-5, 5)); \n    points.push_back(Point(-9, -4)); \n    points.push_back(Point(-2, -9)); \n    printf(\"%.3lf\\n\", rotatingCalipers(points)); \n    return 0; \n} \n");

head.push("半平面交");

desc.push([]);

show.push(function(context) {});

code.push("");

head.push("Voronoi图");

desc.push([]);

show.push(function(context) {});

code.push("");

head.push("Delaunay三角剖分");

desc.push([]);

show.push(function(context) {});

code.push("");

head.push("总结");

desc.push(["计算几何"]);

show.push(function(context) {
    var segment = Segment();
    segment.u.x = 9 * Math.cos(0);
    segment.u.y = 9 * Math.sin(0);
    for (var i = 1; i < 10000; ++i) {
        segment.v.x = 9 * Math.cos(i / 100) * Math.cos(8 * i / 100) * Math.cos(6 * i / 100);
        segment.v.y = 9 * Math.sin(i / 100) * Math.cos(8 * i / 100) * Math.cos(6 * i / 100);
        drawSegment(context, segment);
        segment.u.x = segment.v.x;
        segment.u.y = segment.v.y;
    }
});

code.push("#include <cmath> \n#include <cstdio> \n#include <cstring> \n#include <vector> \n#include <algorithm> \nusing namespace std; \nconst double EPS = 1e-8; \nconst double PI = acos(-1.0); \n \nint dblcmp(double x) \n{ \n    if (fabs(x) < EPS) \n    { \n        return 0; \n    } \n    return x > 0 ? 1 : -1; \n} \n \nstruct Point \n{ \n    double x, y; \n    Point() \n    { \n        x = 0.0; \n        y = 0.0; \n    } \n    Point(double x, double y) \n    { \n        this->x = x; \n        this->y = y; \n    } \n    inline void input() \n    { \n        scanf(\"%lf%lf\", &x, &y); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf\\n\", x, y); \n    } \n    inline double length() const \n    { \n        return sqrt(x * x + y * y); \n    } \n    inline Point norm() const \n    { \n        Point norm; \n        norm.x = x / length(); \n        norm.y = y / length(); \n        return norm; \n    } \n}; \n \nPoint operator +(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x + b.x; \n    c.y = a.y + b.y; \n    return c; \n} \n \nPoint operator -(const Point &a, const Point &b) \n{ \n    Point c; \n    c.x = a.x - b.x; \n    c.y = a.y - b.y; \n    return c; \n} \n \ndouble operator *(const Point &a, const Point &b) \n{ \n    return a.x * b.x + a.y * b.y; \n} \n \ndouble operator ^(const Point &a, const Point &b) \n{ \n    return a.x * b.y - a.y * b.x; \n} \n \nPoint operator *(const Point &a, const double b) \n{ \n    Point c; \n    c.x = a.x * b; \n    c.y = a.y * b; \n    return c; \n} \n \nPoint operator /(const Point &a, const double b) \n{ \n    Point c; \n    c.x = a.x / b; \n    c.y = a.y / b; \n    return c; \n} \n \nbool operator ==(const Point &a, const Point &b) \n{ \n    return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0; \n} \n \ndouble dist(const Point &a, const Point &b) \n{ \n    return (a - b).length(); \n} \n \ndouble cross(const Point &a, const Point &b, const Point &o) \n{ \n    return (a - o) ^ (b - o); \n} \n \ndouble angle(const Point &a, const Point &b) \n{ \n    return atan2(b.y - a.y, b.x - a.x); \n} \n \ndouble angle(const Point &a, const Point &b, const Point &o) \n{ \n    return angle(b, o) - angle(a, o); \n} \n \nstruct Line \n{ \n    double a, b, c; \n    Line() \n    { \n        a = b = c = 0.0; \n    } \n    Line(double a, double b, double c) \n    { \n        this->a = a; \n        this->b = b; \n        this->c = c; \n    } \n    inline void input() \n    { \n        scanf(\"%lf %lf %lf\", &a, &b, &c); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf %.3lf\\n\", a, b, c); \n    } \n}; \n \ndouble dist(const Point &point, const Line &line) \n{ \n    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b); \n} \n \nbool isIntersect(const Point &point ,const Line &line) \n{ \n    return dblcmp(line.a * point.x + line.b * point.y + line.c) == 0; \n} \n \n \nbool isParallel(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b - a.b * b.a) == 0; \n} \n \nbool isVertical(const Line &a, const Line &b) \n{ \n    return dblcmp(a.a * b.b + a.b * b.a) == 0; \n} \n \nPoint intersectPoint(const Line &a, const Line &b) \n{ \n    double a1 = a.a, b1 = a.b, c1 = a.c; \n    double a2 = b.a, b2 = b.b, c2 = b.c; \n    Point c; \n    c.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1); \n    c.y = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1); \n    return c; \n} \n \nstruct Segment \n{ \n    Point u, v; \n    Segment() \n    { \n    } \n    Segment(double x1, double y1, double x2, double y2) \n    { \n        u.x = x1; \n        u.y = y1; \n        v.x = x2; \n        v.y = y2; \n    } \n    Segment(const Point &u, const Point &v) \n    { \n        this->u = u; \n        this->v = v; \n    } \n    inline void input() \n    { \n        u.input(); \n        v.input(); \n    } \n    inline void output() const \n    { \n        printf(\"%.3lf %.3lf %.3lf %.3lf\\n\", u.x, u.y, v.x, v.y); \n    } \n    Line line() const \n    { \n        Line line; \n        line.a = u.y - v.y; \n        line.b = v.x - u.x; \n        line.c = u.x * v.y - v.x * u.y; \n        return line; \n    } \n    Line perpendicularBisector() const \n    { \n        Segment bisector; \n        bisector.u = (u + v) * 0.5; \n        bisector.v.x = bisector.u.x + (u.y - v.y); \n        bisector.v.y = bisector.u.y - (u.x - v.x); \n        return bisector.line(); \n    } \n    double length() const \n    { \n        return dist(u, v); \n    } \n}; \n \ndouble dist(const Point &point, const Segment &segment) \n{ \n    return max(min(dist(point, segment.u), dist(point, segment.v)), dist(point, segment.line())); \n} \n \nbool isIntersect(const Point &point ,const Segment &segment) \n{ \n    if (isIntersect(point, segment.line())) \n    { \n        if (dblcmp(segment.u.y - segment.v.y) == 0) \n        { \n            return point.x > min(segment.u.x, segment.v.x) && point.x < max(segment.u.x, segment.v.x); \n        } \n        return point.y > min(segment.u.y, segment.v.y) && point.y < max(segment.u.y, segment.v.y); \n    } \n    return false; \n} \n \nbool inIntersect(const Segment &a, const Segment &b) \n{ \n    return dblcmp(cross(a.u, a.v, b.u)) * dblcmp(cross(a.u, a.v, b.v)) <= 0 && \n        dblcmp(cross(b.u, b.v, a.u)) * dblcmp(cross(b.u, b.v, a.v)) <= 0; \n} \n \nPoint intersectPoint(const Segment &a, const Segment &b) \n{ \n    double area1 = fabs(cross(b.u, b.v, a.u)); \n    double area2 = fabs(cross(b.u, b.v, a.v)); \n    double area = area1 + area2; \n    double scale = area1 / area; \n    Point c; \n    c.x = a.u.x + (a.v.x - a.u.x) * scale; \n    c.y = a.u.y + (a.v.y - a.u.y) * scale; \n    return c; \n} \n \nstruct Triangle \n{ \n    Point a; \n    Point b; \n    Point c; \n    Triangle() \n    { \n    } \n    Triangle(double x1, double y1, double x2, double y2, double x3, double y3) \n    { \n        a.x = x1; \n        a.y = y1; \n        b.x = x2; \n        b.y = y2; \n        c.x = x3; \n        c.y = y3; \n    } \n    Triangle(const Point &a, const Point &b, const Point &c) \n    { \n        this->a = a; \n        this->b = b; \n        this->c = c; \n    } \n    inline void input() \n    { \n        a.input(); \n        b.input(); \n        c.input(); \n    } \n    inline void output() const \n    { \n        a.output(); \n        b.output(); \n        c.output(); \n    } \n    double area() const \n    { \n        return fabs(cross(a, b, c)) * 0.5; \n    } \n    Line medianA() const \n    { \n        return Segment(a, (b + c) * 0.5).line(); \n    } \n    Line medianB() const \n    { \n        return Segment(b, (a + c) * 0.5).line(); \n    } \n    Line medianC() const \n    { \n        return Segment(c, (a + b) * 0.5).line(); \n    } \n    Point centroid() const \n    { \n        return intersectPoint(medianA(), medianB()); \n    } \n    Line altitudeA() const \n    { \n        Segment altitude; \n        altitude.u = a; \n        altitude.v.x = altitude.u.x + (b.y - c.y); \n        altitude.v.y = altitude.u.y - (b.x - c.x); \n        return altitude.line(); \n    } \n    Line altitudeB() const \n    { \n        Segment altitude; \n        altitude.u = b; \n        altitude.v.x = altitude.u.x + (a.y - c.y); \n        altitude.v.y = altitude.u.y - (a.x - c.x); \n        return altitude.line(); \n    } \n    Line altitudeC() const \n    { \n        Segment altitude; \n        altitude.u = c; \n        altitude.v.x = altitude.u.x + (a.y - b.y); \n        altitude.v.y = altitude.u.y - (a.x - b.x); \n        return altitude.line(); \n    } \n    Point orthoCenter() const \n    { \n        return intersectPoint(altitudeA(), altitudeB()); \n    } \n    Line perpendicularBisectorA() const \n    { \n        return Segment(b, c).perpendicularBisector(); \n    } \n    Line perpendicularBisectorB() const \n    { \n        return Segment(a, c).perpendicularBisector(); \n    } \n    Line perpendicularBisectorC() const \n    { \n        return Segment(a, b).perpendicularBisector(); \n    } \n    Point circumCenter() const \n    { \n        return intersectPoint(perpendicularBisectorA(), perpendicularBisectorB()); \n    } \n    double circumscribedCircleRadius() const \n    { \n        double la = (b - c).length(); \n        double lb = (a - c).length(); \n        double lc = (a - b).length(); \n        return la * lb * lc / sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc)); \n    } \n    Line angleBisectorA() const \n    { \n        Segment bisector; \n        bisector.u = a; \n        bisector.v = bisector.u + ((b - a).norm() + (c - a).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Line angleBisectorB() const \n    { \n        Segment bisector; \n        bisector.u = b; \n        bisector.v = bisector.u + ((a - b).norm() + (c - b).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Line angleBisectorC() const \n    { \n        Segment bisector; \n        bisector.u = c; \n        bisector.v = bisector.u + ((a - c).norm() + (b - c).norm()) * 0.5; \n        return bisector.line(); \n    } \n    Point inCircle() const \n    { \n        return intersectPoint(angleBisectorA(), angleBisectorB()); \n    } \n    double inscribedCircleRaidus() const \n    { \n        double la = (b - c).length(); \n        double lb = (a - c).length(); \n        double lc = (a - b).length(); \n        return sqrt((la + lb + lc) * (lb + lc - la) * (la + lc - lb) * (la + lb - lc)) / (la + lb + lc) * 0.5; \n    } \n}; \n \ndouble triangleArea(double la, double lb, double lc) \n{ \n    double p = (la + lb + lc) * 0.5; \n    return sqrt(p * (p - la) * (p - lb) * (p - lc)); \n} \n \nstruct Rectangle \n{ \n    double x, y; \n    double w, h; \n    Rectangle() \n    { \n        x = y = w = h = 0.0; \n    } \n    Rectangle(double x, double y, double w, double h) \n    { \n        this->x = x; \n        this->y = y; \n        this->w = w; \n        this->h = h; \n    } \n    inline void input() \n    { \n        scanf(\"%lf%lf%lf%lf\", &x, &y, &w, &h); \n    } \n    inline void output() \n    { \n        printf(\"%.3lf %.3lf %.3lf %.3lf\", x, y, w, h); \n    } \n    double left() const \n    { \n        return x; \n    } \n    double right() const \n    { \n        return x + w; \n    } \n    double top() const \n    { \n        return y; \n    } \n    double bottom() const \n    { \n        return y + h; \n    } \n    Point leftTop() const \n    { \n        return Point(left(), top()); \n    } \n    Point rightTop() const \n    { \n        return Point(right(), top()); \n    } \n    Point leftBottom() const \n    { \n        return Point(left(), bottom()); \n    } \n    Point rightBottom() const \n    { \n        return Point(right(), bottom()); \n    } \n    Segment toSegment() const \n    { \n        return Segment(leftTop(), rightBottom()); \n    } \n}; \n \nstruct Circle \n{ \n    Point o; \n    double radius; \n    Circle() \n    { \n        radius = 0.0; \n    } \n    Circle(double x, double y, double radius) \n    { \n        o.x = x; \n        o.y = y; \n        this->radius = radius; \n    } \n    Circle(const Point &o, double radius) \n    { \n        this->o = o; \n        this->radius = radius; \n    } \n    inline void input() \n    { \n        o.input(); \n        scanf(\"%lf\", &radius); \n    } \n    inline void output() \n    { \n        printf(\"%.3lf %.3lf %.3lf\\n\", o.x, o.y, radius); \n    } \n}; \n \ndouble dist(const Circle &a, const Circle &b) \n{ \n    return dist(a.o, b.o); \n} \n \nstruct Polygon \n{ \n    vector<Point> vertex; \n}; \n \nint main() \n{ \n    return 0; \n} \n");

window.onload = function() {
    setContent(head, desc, show, code);
}
