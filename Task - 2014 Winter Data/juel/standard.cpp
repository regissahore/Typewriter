#include <iostream>
#include <stdio.h>
#include <set>
#include <string.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <queue>
#include <math.h>
#define ll long long
using namespace std;
const double pi=acos(-1.0);
int n;
const int N=15;
ll a[N],dp[N];
ll cal()
{
    dp[0]=a[0]+1;
    for(int i=1;i<=n;i++) dp[i]=dp[i-1]*a[i]+1;
    return dp[n-1];
}
int main()
{

    int t=1;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%lld",&a[i]);
        }

        sort(a,a+n);
		printf("%lld\n",cal());
    }

    return 0;
}
