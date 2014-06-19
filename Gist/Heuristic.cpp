#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
int DIR_X[] = {1, 0, -1, 0};
int DIR_Y[] = {0, 1, 0, -1};
int START = 283164705;
int TARGET = 123804765;

int getStatus(int m[3][3])
{
    int status = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            status = status * 10 + m[i][j];
        }
    }
    return status;
}

int getMat(int status, int m[3][3])
{
    int pos = 0;
    for (int i = 2; i >= 0; --i)
    {
        for (int j = 2; j >= 0; --j)
        {
            m[i][j] = status % 10;
            status /= 10;
            if (m[i][j] == 0)
            {
                pos = i * 3 + j;
            }
        }
    }
    return pos;
}

int getW(int cur[3][3], int target[3][3])
{
    int w = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            w += cur[i][j] != target[i][j];
        }
    }
    return w;
}

struct Node
{
    int status;
    int d, w;
    bool operator <(const Node &node) const
    {
        if (d + w == node.d + node.w)
        {
            return d > node.d;
        }
        return d + w > node.d + node.w;
    }
};

void printNode(Node &node)
{
    int mat[3][3];
    getMat(node.status, mat);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (mat[i][j])
            {
                printf("%d ", mat[i][j]);
            }
            else
            {
                printf("  ");
            }
        }
        putchar('\n');
    }
    printf("d = %d  w = %d  f = %d\n\n", node.d, node.w, node.d + node.w);
}

void search()
{
    int start[3][3];
    int target[3][3];
    getMat(START, start);
    getMat(TARGET, target);
    priority_queue<Node> q;
    set<int> visit;
    visit.insert(START);
    Node s;
    s.status = START;
    s.d = 0;
    s.w = getW(start, target);
    q.push(s);
    while (not q.empty())
    {
        Node u = q.top();
        q.pop();
        puts("Head");
        printNode(u);
        int cur[3][3];
        int pos = getMat(u.status, cur);
        int x = pos / 3;
        int y = pos % 3;
        puts("Find");
        for (int k = 0; k < 4; ++k)
        {
            int tx = x + DIR_X[k];
            int ty = y + DIR_Y[k];
            if (tx >= 0 && tx < 3)
            {
                if (ty >= 0 && ty < 3)
                {
                    int next[3][3];
                    memcpy(next, cur, sizeof(cur));
                    swap(next[x][y], next[tx][ty]);
                    Node v;
                    v.status = getStatus(next);
                    v.d = u.d + 1;
                    v.w = getW(next, target);
                    if (visit.find(v.status) == visit.end())
                    {
                        visit.insert(v.status);
                        q.push(v);
                        printNode(v);
                        if (v.status == TARGET)
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    search();
    return 0;
}
