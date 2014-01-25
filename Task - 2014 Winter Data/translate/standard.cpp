#include <iostream>
#include <stdio.h>
using namespace std;
bool v[1000009];
int a,top,tail,n,m,queue[200009],ans;
int main()
{
    scanf("%d %d",&m,&n);
    top=1,tail=0,ans=0;
    for (int i=1; i<=n; ++i)
    {
        scanf("%d",&a);
        if (!v[a])
        {
            ++ans;
            if (tail-top+1<m)
            {
                queue[++tail]=a;
                v[a]=true;
            }
            else
            {
                v[queue[top]]=false;
                top++;
                queue[++tail]=a;
                v[a]=true;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
