#include <iostream>

using namespace std;

int main()
{
    int a,b,c;
    cin>>a>>c>>b;
    int sum=0,rest=0;
    while (a)
    {
        sum+=a;
        rest+=a;
        a=rest/b;
        rest-=a*b;
    }
    cout<<sum*c<<endl;
    return 0;
}
