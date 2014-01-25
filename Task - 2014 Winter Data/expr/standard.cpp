#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
const int MAX_N = 5000000;
const int INF = 10000;
char s[MAX_N];
int ans = 0;
int length;
void init()
{
	gets(s); //读取字符串
	length=strlen(s); //测长度
}
void work()
{
	int i,j,k,tmp,ctmp; //tmp表示当前数字 ctmp表示乘法当中的数字
	i=0;
	while (i<length)
	{
		ctmp = 0;
		tmp = 0; //初始化
		j=i;
		while (j<length&&s[j]>='0'&&s[j]<='9') //如果没有扫描完 并且是数字
		{
			tmp=tmp*10+(s[j]-'0'); //*10+ 把字符串还原为数字
			j++;
		}
		tmp%=INF; //mod 1k
		ctmp=tmp; //乘法第一项就是tmp
		while (j<length&&s[j]=='*') //从后面起将一个数字和一个字符作为一组，扫描了数字，如果后面是* 继续乘法
		{                             //否则 就是+（题目保证）
			k=j+1;
			tmp = 0;
			while (k<length&&s[k]>='0'&&s[k]<='9')
			{
				tmp = tmp*10+(s[k]-'0'); //*10+
				k++;
			}
			tmp%=INF; //注意先余 否则int_max*1k会大于int_max
			ctmp = ctmp*tmp%INF;
			j=k;
		}
		ans = (ans+ctmp)%INF; //作为一个加法的结束
		i=j+1;
	}
}
void put()
{
	printf("%d\n",ans);
}
int main()
{
	init();
	work();
	put();
	return 0;
}
