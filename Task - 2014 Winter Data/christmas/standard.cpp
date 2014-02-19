#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int MAXN=1000009,MAXM=1000009;
int head[MAXN],next[MAXM],to[MAXM],p[MAXN][20],dep[MAXN],id,q;
void init()
{
    id=0;
    memset(head,-1,sizeof(head));
    memset(p,-1,sizeof(p));
    memset(dep,-1,sizeof(dep));
}
void add(int u,int v)
{
    to[id]=v;
    next[id]=head[u];
    head[u]=id++;
}
void dfs(int u)
{
    for (int i=head[u]; ~i; i=next[i])
    {
        int v=to[i];
        if (dep[v]==-1)
        {
            dep[v]=dep[u]+1;
            p[v][0]=u;
            for (int j=1; (1<<j)<=dep[v]; ++j)
            {
                p[v][j]=p[p[v][j-1]][j-1];
            }
            dfs(v);
        }
    }
}
int lca(int u,int v)
{
    if (dep[v]>dep[u])
    {
        swap(u,v);
    }
    int det=dep[u]-dep[v];
    for (int i=0; i<=19; ++i)
    {
        if ((1 << i) & det)
        {
            u = p[u][i];
        }
    }
    if (u==v) return u;
    for (int i=19; i>=0; --i)
    {
        if (p[u][i]!=p[v][i])
        {
            u=p[u][i];
            v=p[v][i];
        }
    }
    u=p[u][0];
    return u;
}
int main()
{
    //freopen("in.txt","r",stdin);
    init();
    scanf("%d",&q);
    dep[1]=0;
    add(1,2);
    add(1,3);
    add(1,4);
    dfs(1);
    int tot=4,n1=2,n2=3,ans=2;
    for (int i=1; i<=q; ++i)
    {
        int u;
        scanf("%d",&u);
        add(u,++tot);
        add(u,++tot);
        dfs(u);
        int p1=lca(tot-1,n1);
        int t1=dep[tot-1]+dep[n1]-2*dep[p1];
        int p2=lca(tot,n2);
        int t2=dep[tot]+dep[n2]-2*dep[p2];
        if (t1>ans && t1>=t2)
        {
            ans=t1;
            n2=tot-1;
        }
        else if (t2>ans && t2>=t1)
        {
            ans=t2;
            n1=tot;
        }
        printf("%d\n",ans);
    }
    return 0;
}
