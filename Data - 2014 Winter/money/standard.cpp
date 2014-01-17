#include <iostream>
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
struct A
{
    int val,num;
} a[3*100000+9];
bool cmp(A x,A y)
{
    return x.val<y.val;
}
int ans[3*100000+9];
int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    cin>>n;
    for (int i=1; i<=n; ++i)
    {
        cin>>a[i].val;
        a[i].num=i;
    }
    sort(a+1,a+1+n,cmp);
    for (int i=1; i<=n; ++i)
    {
        if (a[i].val>a[i-1].val)
        {
            ans[a[i].num]=a[i].val;
        }
        else
        {
            a[i].val=a[i-1].val+1;
            ans[a[i].num]=a[i].val;
        }
    }
    long long tot=0;
    for (int i=1; i<=n; ++i)
    {
        tot+=ans[i];
    }
    cout<<tot<<endl;
    return 0;
}
