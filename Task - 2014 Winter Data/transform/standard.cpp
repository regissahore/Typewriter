#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int s1[5009],s2[5009],a[5009],b[5009];
int main()
{
    int n, t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d",&n);
        memset(s1,0,sizeof(s1));
        memset(s2,0,sizeof(s2));
        for (int i=1; i<=n; i++)
        {
            scanf("%d",&a[i]);
            s1[i]=s1[i-1]+a[i];
        }
        for (int i=1; i<=n; i++)
        {
            scanf("%d",&b[i]);
            s2[i]=s2[i-1]+b[i];
        }
        sort(s1+1,s1+1+n);
        sort(s2+1,s2+1+n);
        bool can=true;
        for (int i=1; i<=n; i++)
        {
            if (s1[i]!=s2[i])
            {
                can=false;
                break;
            }
        }
        if (can)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
