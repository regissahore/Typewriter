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
	gets(s); //��ȡ�ַ���
	length=strlen(s); //�ⳤ��
}
void work()
{
	int i,j,k,tmp,ctmp; //tmp��ʾ��ǰ���� ctmp��ʾ�˷����е�����
	i=0;
	while (i<length)
	{
		ctmp = 0;
		tmp = 0; //��ʼ��
		j=i;
		while (j<length&&s[j]>='0'&&s[j]<='9') //���û��ɨ���� ����������
		{
			tmp=tmp*10+(s[j]-'0'); //*10+ ���ַ�����ԭΪ����
			j++;
		}
		tmp%=INF; //mod 1k
		ctmp=tmp; //�˷���һ�����tmp
		while (j<length&&s[j]=='*') //�Ӻ�����һ�����ֺ�һ���ַ���Ϊһ�飬ɨ�������֣����������* �����˷�
		{                             //���� ����+����Ŀ��֤��
			k=j+1;
			tmp = 0;
			while (k<length&&s[k]>='0'&&s[k]<='9')
			{
				tmp = tmp*10+(s[k]-'0'); //*10+
				k++;
			}
			tmp%=INF; //ע������ ����int_max*1k�����int_max
			ctmp = ctmp*tmp%INF;
			j=k;
		}
		ans = (ans+ctmp)%INF; //��Ϊһ���ӷ��Ľ���
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
