#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;

int a[MAXN][MAXN];
int x[MAXN * MAXN], y[MAXN * MAXN], top;

int main()
{
    int n, m, k, s;
    int caseNum = 0;
    char s1[10];
    char s2[10];
    while (~scanf("%d%d%d%d", &n, &m, &k, &s))
    {
        int minNum = 0x7fffffff;
        char temp[10];
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                scanf("%s", temp);
                a[i][j] = 0;
                for (int k = 0; k < 3; ++k)
                {
                    a[i][j] = a[i][j] * 26 + temp[k] - 'a';
                }
                minNum = min(minNum, a[i][j]);
            }
        }
        s1[0] = minNum / 26 / 26 + 'a';
        s1[1] = ((minNum / 26) % 26) + 'a';
        s1[2] = (minNum % 26) + 'a';
        s1[3] = 0;
        int count = 0;
        top = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (a[i][j] == minNum)
                {
                    ++count;
                    x[top] = i;
                    y[top++] = j;
                }
            }
        }
        if (count > ((n + k) / (k + 1)) * ((m + k) / (k + 1)))
        {
            strcpy(s2, s1);
        }
        else
        {
            int nextMin = 0x7fffffff;
            for (int l = 0; l < top; ++l)
            {
                int top = max(x[l] - k, 0);
                int bottom = min(x[l] + k, n - 1);
                int left = max(y[l] - k, 0);
                int right = min(y[l] + k, m - 1);
                for (int i = top; i <= bottom; ++i)
                {
                    for (int j = left; j <= right; ++j)
                    {
                        if (i != x[l] || j != y[l])
                        {
                            nextMin = min(nextMin, a[i][j]);
                        }
                    }
                }
            }
            s2[0] = nextMin / 26 / 26 + 'a';
            s2[1] = ((nextMin / 26) % 26) + 'a';
            s2[2] = (nextMin % 26) + 'a';
            s2[3] = 0;
        }
        for (int i = 0; i <= s; ++i)
        {
            printf("%s", i & 1 ? s2 : s1);
        }
        putchar('\n');
    }
    return 0;
}
