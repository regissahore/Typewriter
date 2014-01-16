#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char a[2000],b[2000];
int c[2009];
int main()
{
    int n;
    scanf("%d\n",&n);
    scanf("%s",a);
    scanf("%s",b);
    int la=strlen(a),lb=strlen(b),l=la+lb-1;
    for (int i=0; i<la/2; ++i)
    {
        swap(a[i],a[la-i-1]);
    }
    for (int i=0; i<lb/2; ++i)
    {
        swap(b[i],b[lb-i-1]);
    }
    for (int i=0; a[i]; ++i)
    {
        for (int j=0; b[j]; ++j)
        {
            c[i+j]+=(a[i]-'0')*(b[j]-'0');
        }
    }
    int r=0;
    for (int i=0; i<l; ++i)
    {
        c[i]=c[i]+r;
        r=c[i]/n;
        c[i]%=n;
    }
    if (r)
    {
        c[l++]=r;
    }
    for (int i=l-1; i>=0; --i)
    {
        printf("%c",c[i]+'0');
    }
    printf("\n");
    return 0;
}
