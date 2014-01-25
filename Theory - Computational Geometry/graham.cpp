#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
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
    bool operator <(const Point &point) const
    {
        if (y == point.y)
        {
            return x < point.x;
        }
        return y < point.y;
    }
};

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

double cross(const Point &a, const Point &b, const Point &o)
{
    return (a - o) ^ (b - o);
}

struct Polygon
{
    vector<Point> vertex;
    inline void output()
    {
        for (size_t i = 0; i < vertex.size(); ++i)
        {
            vertex[i].output();
        }
    }
};

void graham(vector<Point> &points, Polygon &convex)
{
    convex.vertex.clear();
    sort(points.begin(), points.end());
    convex.vertex.push_back(points[0]);
    convex.vertex.push_back(points[1]);
    for (size_t i = 2; i < points.size(); ++i)
    {
        while (convex.vertex.size() >= 2)
        {
            if (dblcmp((points[i] - convex.vertex[convex.vertex.size() - 1]) ^ (convex.vertex[convex.vertex.size() - 1] - convex.vertex[convex.vertex.size() - 2])) <= 0)
            {
                break;
            }
            convex.vertex.pop_back();
        }
        convex.vertex.push_back(points[i]);
    }
    convex.vertex.push_back(points[points.size() - 2]);
    int top = convex.vertex.size();
    for (int i = points.size() - 3; i >= 0; --i)
    {
        while (convex.vertex.size() >= top)
        {
            if (dblcmp((points[i] - convex.vertex[convex.vertex.size() - 1]) ^ (convex.vertex[convex.vertex.size() - 1] - convex.vertex[convex.vertex.size() - 2])) <= 0)
            {
                break;
            }
            convex.vertex.pop_back();
        }
        convex.vertex.push_back(points[i]);
    }
}

int main()
{
    vector<Point> points;
    points.push_back(Point(1, 2));
    points.push_back(Point(4, -4));
    points.push_back(Point(-5, 5));
    points.push_back(Point(-3, -8));
    points.push_back(Point(-2, -9));
    points.push_back(Point(8, 2));
    points.push_back(Point(-9, -4));
    points.push_back(Point(6, -6));
    points.push_back(Point(4, -2));
    points.push_back(Point(7, 7));
    points.push_back(Point(-1, 6));
    Polygon polygon;
    graham(points, polygon);
    polygon.output();
    return 0;
}
