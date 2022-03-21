#include <iostream>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 100	//������������
struct goods	//��Ʒ�ṹ��
{
	int sign;	//��Ʒ���
	int w;	//��Ʒ����
	int p;	//��Ʒ��ֵ
}a[N];
bool m(goods a,goods b)
{
	return (a.p/a.w)>(b.p/b.w);
}
int max(int a,int b)
{
	return a<b?b:a;
}
int n,C,bestP=0,cp=0,cw=0;
int X[N],cx[N];

/*��̬�滮�����0/1��������*/
int KnapSack1(int n,goods a[],int C,int x[])
{
    int j;
	int V[N][10*N];
	for(int i=0;i<=n;i++)	//��ʼ����0��
		V[i][0]=0;
	for(int j=0;j<=C;j++)	//��ʼ����0��
		V[0][j]=0;
	for(int i=1;i<=n;i++)		//�����i�У����е�i�ε���
		for(int j=1;j<=C;j++)
			if(j<a[i-1].w)
				V[i][j]=V[i-1][j];
			else
				V[i][j]=max(V[i-1][j],V[i-1][j-a[i-1].w]+a[i-1].p);
			j=C;	//��װ�뱳������Ʒ
			for (int i=n;i>0;i--)
			{
				if (V[i][j]>V[i-1][j]){
					x[i-1]=1;
					j=j-a[i-1].w;
				}
				else	x[i-1]=0;
			}
			return V[n][C];	//���ر���ȡ�õ�����ֵ
}
/*���ݷ����0/1��������*/
int BackTrack(int i)
{
	if(i>n-1){
		if(bestP<cp){
			for (int k=0;k<n;k++)	X[k]=cx[k];//�洢����·��
			bestP=cp;
		}
		return bestP;
	}
	if(cw+a[i].w<=C){	//����������
		cw=cw+a[i].w;
		cp=cp+a[i].p;
		cx[a[i].sign]=1;	//װ�뱳��
		BackTrack(i+1);
		cw=cw-a[i].w;
		cp=cp-a[i].p;	//���ݣ�����������
	}
	cx[a[i].sign]=0;	//��װ�뱳��
	BackTrack(i+1);
	return bestP;
}
int KnapSack2(int n,goods a[],int C,int x[])
{
	for(int i=0;i<n;i++)
	{
		x[i]=0;
		a[i].sign=i;
	}
	sort(a,a+n,m);//������Ʒ����λ������ֵ��������
	BackTrack(0);
	return bestP;
}

/*���������㷨��������*/
int main()
{
	goods b[N];
	printf("��Ʒ����n: ");
	scanf("%d",&n);	//������Ʒ����
	printf("��������C: ");
	scanf("%d",&C);	//���뱳������

	for (int i=0;i<n;i++)	//������Ʒi������w�����ֵv
	{
		printf("��Ʒ%d������w[%d]�����ֵv[%d]:  ",i+1,i+1,i+1);
		scanf("%d%d",&a[i].w,&a[i].p);
		b[i]=a[i];
	}

	int sum1=KnapSack1(n,a,C,X);//���ö�̬�滮����0/1��������
	printf("��̬�滮�����0/1��������:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//�������X[n]����
	printf("]	װ���ܼ�ֵ%d\n",sum1);
	for (int i=0;i<n;i++)
	{
		a[i]=b[i];
	}//�ָ�a[N]˳��
	int sum2=KnapSack2(n,a,C,X);//���û��ݷ���0/1��������
	printf("���ݷ����0/1��������:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//�������X[n]����
	printf("]	װ���ܼ�ֵ%d\n",sum2);
	for (int i=0;i<n;i++)
	{
		a[i]=b[i];
	}//�ָ�a[N]˳��

	return 0;
}
