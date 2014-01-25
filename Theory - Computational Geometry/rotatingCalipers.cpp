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
    inline double length() const
    {
        return sqrt(x * x + y * y);
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

double dist(const Point &a, const Point &b)
{
    return (a - b).length();
}

double rotatingCalipers(vector<Point> &points)
{
    double ans = 0.0;
    points.push_back(points[0]);
    for (int i = 0, j = 1; i < points.size(); ++i)
    {
        while (fabs(cross(points[i], points[i + 1], points[j + 1])) > fabs(cross(points[i], points[i + 1], points[j])))
        {
            j = (j + 1) % (points.size() - 1);
        }
        ans = max(ans, max(dist(points[i], points[j]), dist(points[i + 1], points[j])));
    }
    return ans;
}

int main()
{
    vector<Point> points;
    points.push_back(Point(-2, -9));
    points.push_back(Point(6, -6));
    points.push_back(Point(8, 2));
    points.push_back(Point(7, 7));
    points.push_back(Point(-1, 6));
    points.push_back(Point(-5, 5));
    points.push_back(Point(-9, -4));
    points.push_back(Point(-2, -9));
    printf("%.3lf\n", rotatingCalipers(points));
    return 0;
}
