#include <iostream>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 100	//最多可能物体数
struct goods	//物品结构体
{
	int sign;	//物品序号
	int w;	//物品重量
	int p;	//物品价值
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

/*动态规划法求解0/1背包问题*/
int KnapSack1(int n,goods a[],int C,int x[])
{
    int j;
	int V[N][10*N];
	for(int i=0;i<=n;i++)	//初始化第0列
		V[i][0]=0;
	for(int j=0;j<=C;j++)	//初始化第0行
		V[0][j]=0;
	for(int i=1;i<=n;i++)		//计算第i行，进行第i次迭代
		for(int j=1;j<=C;j++)
			if(j<a[i-1].w)
				V[i][j]=V[i-1][j];
			else
				V[i][j]=max(V[i-1][j],V[i-1][j-a[i-1].w]+a[i-1].p);
			j=C;	//求装入背包的物品
			for (int i=n;i>0;i--)
			{
				if (V[i][j]>V[i-1][j]){
					x[i-1]=1;
					j=j-a[i-1].w;
				}
				else	x[i-1]=0;
			}
			return V[n][C];	//返回背包取得的最大价值
}
/*回溯法求解0/1背包问题*/
int BackTrack(int i)
{
	if(i>n-1){
		if(bestP<cp){
			for (int k=0;k<n;k++)	X[k]=cx[k];//存储最优路径
			bestP=cp;
		}
		return bestP;
	}
	if(cw+a[i].w<=C){	//进入左子树
		cw=cw+a[i].w;
		cp=cp+a[i].p;
		cx[a[i].sign]=1;	//装入背包
		BackTrack(i+1);
		cw=cw-a[i].w;
		cp=cp-a[i].p;	//回溯，进入右子树
	}
	cx[a[i].sign]=0;	//不装入背包
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
	sort(a,a+n,m);//将各物品按单位重量价值降序排列
	BackTrack(0);
	return bestP;
}

/*测试以上算法的主函数*/
int main()
{
	goods b[N];
	printf("物品种数n: ");
	scanf("%d",&n);	//输入物品种数
	printf("背包容量C: ");
	scanf("%d",&C);	//输入背包容量

	for (int i=0;i<n;i++)	//输入物品i的重量w及其价值v
	{
		printf("物品%d的重量w[%d]及其价值v[%d]:  ",i+1,i+1,i+1);
		scanf("%d%d",&a[i].w,&a[i].p);
		b[i]=a[i];
	}

	int sum1=KnapSack1(n,a,C,X);//调用动态规划法求0/1背包问题
	printf("动态规划法求解0/1背包问题:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//输出所求X[n]矩阵
	printf("]	装入总价值%d\n",sum1);
	for (int i=0;i<n;i++)
	{
		a[i]=b[i];
	}//恢复a[N]顺序
	int sum2=KnapSack2(n,a,C,X);//调用回溯法求0/1背包问题
	printf("回溯法求解0/1背包问题:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//输出所求X[n]矩阵
	printf("]	装入总价值%d\n",sum2);
	for (int i=0;i<n;i++)
	{
		a[i]=b[i];
	}//恢复a[N]顺序

	return 0;
}
