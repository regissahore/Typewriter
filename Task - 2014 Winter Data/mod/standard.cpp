#include<cstdio>
#include<iostream>
#include<cstdlib>
using namespace std;
int extgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    int t=extgcd(b,a%b,x,y);
    int tmp=x;
    x=y;
    y=tmp-a/b*y;
    return t;
}
int main()//a*x%b==1%b
{
    int x,y,a,b;
    scanf("%d%d",&a,&b);
    extgcd(a,b,x,y);
    while(x>0)        x-=b ;
    while(x<=0)        x+=b ;
    printf("%d",x);
    return 0;
}