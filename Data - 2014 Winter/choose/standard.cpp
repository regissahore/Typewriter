#include <iostream>
#include <stdio.h>
#include <algorithm>
const int MAXN=100009,MAXM=100009;
using namespace std;
long long a[MAXN],b[MAXN],n,m;
long long absx(long long x)
{
    if (x>=0) return x;
    return -x;
}
int main()
{
    //freopen("in.txt","r",stdin);
    while (~scanf("%lld %lld",&m,&n))
    {
        for (int i=1; i<=m; ++i)
        {
            scanf("%lld",&b[i]);
        }
        for (int i=1 ;i<=n; ++i)
        {
            scanf("%lld",&a[i]);
        }

        sort(a+1,a+1+n);
        sort(b+1,b+1+m);
        int now=1;
        long long ans=0;
        for (int i=1; i<=n; ++i)
        {
            while (absx(a[i]-b[now])>=absx(a[i]-b[now+1]) && now<=m) now++;
            ans+=absx(a[i]-b[now]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
