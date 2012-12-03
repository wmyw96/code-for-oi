#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;

typedef long long LL;
const int MAX_N=201;
LL c[MAX_N][MAX_N],b[MAX_N][MAX_N],a[MAX_N][MAX_N],d[MAX_N][MAX_N];
int n,m,k;

void Mul2(){
	memset(c,0,sizeof c);
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n+1;j++)
			if (b[i][j])
				for (int k=1;k<=n+1;k++)
					c[i][k]+=b[i][j]*b[j][k];
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n+1;j++) b[i][j]=c[i][j];
}

void Mul1(){
	memset(c,0,sizeof c);
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n+1;j++)
			if (b[i][j])
				for (int k=1;k<=n+1;k++)
					c[i][k]+=b[i][j]*a[j][k];
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n+1;j++) b[i][j]=c[i][j];
}

void Mul(){
	memset(c,0,sizeof c);
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=1;j++)
			for (int k=1;k<=n+1;k++)
				c[i][j]+=b[i][k]*d[k][j];
	for (int i=1;i<=n+1;i++) d[i][1]=c[i][1];
}
void calc(int nn){
	if (nn==0) return;
	if (nn==1){
		for (int i=1;i<=n+1;i++)
		    for (int j=1;j<=n+1;j++)
		       b[i][j]=a[i][j];
		return;
	}
	calc(nn/2);
	Mul2();
	if (nn%2) Mul1();
}
/*
void see(){
		for (int i=1;i<=n+1;i++){
			for (int j=1;j<=n+1;j++)
				printf("%d ",b[i][j]);
			printf("\n");
		}
}
*/
int main(){
	while (scanf("%d%d%d",&n,&m,&k)!=EOF){
		if (n==0) return 0;
		memset(a,0,sizeof a);
		for (int i=1;i<=n+1;i++) a[i][i]=1;
		for (int i=1;i<=k;i++){
			char ch;int p,q;
			scanf(" %c",&ch);
			//printf("%c\n",ch);
			if (ch=='g'){
				scanf("%d",&p);
				a[p][n+1]++;
			}
			if (ch=='e'){
				scanf("%d",&p);
				for (int j=1;j<=n+1;j++) a[p][j]=0;
			}
			if (ch=='s'){
				scanf("%d%d",&p,&q);
				for (int j=1;j<=n+1;j++) swap(a[p][j],a[q][j]);
			}
			//see();
		}
		calc(m);
		
		//see();

		memset(d,0,sizeof d);
		d[n+1][1]=1;
		Mul();
		for (int i=1;i<n;i++)
			printf("%I64d ",d[i][1]);
		printf("%I64d\n",d[n][1]);
	}
}

