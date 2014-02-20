#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;

int n, m;
struct Edge
{
    int u, v;
    double a, b;
    double w;
    inline void input()
    {
        scanf("%d%d", &u, &v);
        scanf("%lf%lf", &a, &b);
    }
    bool operator <(const Edge &edge) const
    {
        return w < edge.w;
    }
} edge[MAXN];

int father[MAXN];

void init()
{
    for (int i = 1; i <= n; ++i)
    {
        father[i] = i;
    }
}

int find(int x)
{
    if (x == father[x])
    {
        return x;
    }
    return father[x] = find(father[x]);
}

void combine(int x, int y)
{
    father[find(x)] = find(y);
}

bool judge(double w)
{
    for (int i = 0; i < m; ++i)
    {
        edge[i].w = edge[i].a - edge[i].b * w;
    }
    sort(edge, edge + m);
    double total = 0.0;
    init();
    for (int i = 0; i < m; ++i)
    {
        int u = edge[i].u;
        int v = edge[i].v;
        if (find(u) != find(v))
        {
            combine(u, v);
            total += edge[i].w;
        }
    }
    return total <= 0.0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        edge[i].input();
    }
    double l = 0.0, r = 1e10;
    while (r - l > 1e-3)
    {
        double mid = (l + r) * 0.5;
        if (judge(mid))
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    printf("%.2lf\n", (l + r) * 0.5);
    return 0;
}
