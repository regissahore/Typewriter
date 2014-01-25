#include <iostream>
#include <stdio.h>

using namespace std;
const long long mod1=1000000007,mod2=99991;
char a[100009],b[100009],x[100009],y[100009];
int main()
{
    scanf("%s",a);
    scanf("%s",b);
    long long ta1=0,ta2=0,tb1=0,tb2=0;
    for (int j=0; a[j]; ++j)
    {
        ta1=ta1*10+(a[j]-'0');
        ta1%=mod1;
        ta2=ta2*10+(a[j]-'0');
        ta2%=mod2;
    }
    for (int j=0; b[j]; ++j)
    {
        tb1=tb1*10+(b[j]-'0');
        tb1%=mod1;
        tb2=tb2*10+(b[j]-'0');
        tb2%=mod2;
    }
    int n,ans=0;
    scanf("%d",&n);
    for (int i=1; i<=n; ++i)
    {
        scanf("%s",x);
        scanf("%s",y);
        long long tx1=0,tx2=0,ty1=0,ty2=0;
        for (int j=0; x[j]; ++j)
        {
            tx1=tx1*10+(x[j]-'0');
            tx1%=mod1;
            tx2=tx2*10+(x[j]-'0');
            tx2%=mod2;
        }
        for (int j=0; y[j]; ++j)
        {
            ty1=ty1*10+(y[j]-'0');
            ty1%=mod1;
            ty2=ty2*10+(y[j]-'0');
            ty2%=mod2;
        }
        if ((ta1*tx1%mod1+tb1)%mod1==ty1%mod1 && (ta2*tx2%mod2+tb2)%mod2==ty2%mod2)
        {
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
