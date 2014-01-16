#include <cstdio>
#include <algorithm>
using std::sort;
const int N=1001;
struct info{
    int a[5000];
    void print(){
        if (!a[0]) puts("0");
        else for (int i=a[0];i;i--) printf("%d",a[i]);
    }
}ans,sum,one,zero,save;
struct inim{
    int x,y;
    inim(const int a=0,const int b=0):
        x(a),y(b){}
}im[N];
inline bool cmp(inim x,inim y){ return x.x*x.y<y.x*y.y; }
inline info operator *(info a,int b){
    info res;
    int x=0,l=a.a[0];
    for (int i=1;i<=l;i++){
        x+=a.a[i]*b;
        res.a[i]=x%10;
        x/=10;
    }
    while (x) res.a[++l]=x%10,x/=10;
    res.a[0]=l;
    return res;
}
inline info operator /(info a,int b){
    info res;
    int x=0,l=a.a[0];
    for (int i=l;i;i--){
        x=x*10+a.a[i];
        res.a[i]=x/b;
        x%=b;
    }
    while (!res.a[l] && l) --l;
    res.a[0]=l;
    return res;
}
inline bool operator >(info a,info b){
    if (a.a[0]>b.a[0]) return 1;
    if (a.a[0]<b.a[0]) return 0;
    for (int i=a.a[0];i;i--){
        if (a.a[i]>b.a[i]) return 1;
        if (a.a[i]<b.a[i]) return 0;
    }
    return 0;
}
int n,xx,yy;
int main(){
    scanf("%d",&n);
    scanf("%d%d",&xx,&yy);
    for (int i=1;i<=n;i++) scanf("%d%d",&im[i].x,&im[i].y);
    sort(im+1,im+n+1,cmp);
    zero.a[0]=0;
    one.a[0]=one.a[1]=1;
    sum=one*xx;
    ans=zero;
    for (int i=1;i<=n;i++){
        save=sum/im[i].y;
        if (save>ans) ans=save;
        sum=sum*im[i].x;
    }
    ans.print();
}
