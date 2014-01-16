#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int MAXN=1000009;
int n,m,a[MAXN];
long long add[MAXN],sub[MAXN];
struct ASK
{
    int st,ed,val;
}ask[MAXN];
bool check(int x)
{
    for (int i=1; i<=n; ++i)
    {
        add[i]=sub[i]=0;
    }
    for (int i=1; i<=x; ++i)
    {
        add[ask[i].st]+=ask[i].val;
        sub[ask[i].ed]+=ask[i].val;
    }
    long long now=0;
    for (int i=1; i<=n; ++i)
    {
        now+=add[i];
        if (now>a[i]) return false;
        now-=sub[i];
    }
    return true;
}
int main()
{
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; ++i)
    {
        scanf("%d",&a[i]);
    }
    for (int i=1; i<=m; ++i)
    {
        scanf("%d %d %d",&ask[i].val,&ask[i].st,&ask[i].ed);
    }
    int l=0,r=m,mid,ans=0;
    while (l<=r)
    {
        mid=(l+r)/2;
        if (check(mid))
        {
            l=mid+1;
            ans=mid;
        }
        else
        {
            r=mid-1;
        }
    }
    if (ans==m)
    {
        printf("0\n");
    }
    else
    {
        cout<<-1<<endl;
        cout<<ans+1<<endl;
    }

    return 0;
}
