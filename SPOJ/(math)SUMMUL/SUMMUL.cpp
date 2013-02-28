#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MOD= 1000000007;
typedef long long LL;
int C[101][101];
int A[3][2]; 
int MM[3][3];
const int M[3][3]={
	{3,3,0},
	{0,1,1},
	{0,1,2}
};

void Mul(){
	int n=2, m=1, nm=2;
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=m;j++) C[i][j]=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int k=1;k<=nm;k++){
				C[i][j]+=(LL)MM[i][k]*A[k][j]%MOD;
				C[i][j]%=MOD;
			}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) A[i][j]=C[i][j];
}

void Mul2(){
	int n=2, m=2, nm=2;
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=m;j++) C[i][j]=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int k=1;k<=nm;k++){
				C[i][j]+=(LL)MM[i][k]*MM[k][j]%MOD;
				C[i][j]%=MOD;
			}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) MM[i][j]=C[i][j];	
}

void Mul1(){
	int n=2, m=2, nm=2;
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=m;j++) C[i][j]=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int k=1;k<=nm;k++){
				C[i][j]+=(LL)MM[i][k]*M[k][j]%MOD;
				C[i][j]%=MOD;
			}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) MM[i][j]=C[i][j];	
}

void calc(int n){
	if (n==0) return;
	if (n==1){
		for (int i=1;i<=2;i++)
		    for (int j=1;j<=2;j++) MM[i][j]=M[i][j];
		return;
	}
	calc(n/2);
	Mul2();
	if (n%2) Mul1();
}

int main(){
	int T,n;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		A[0][0]=2;A[0][1]=1;
		A[1][1]=1;
		A[2][1]=2;
		calc(n-1);
		Mul();
		int ans=A[1][1]-n;
		while (ans<0) ans+=MOD;
		if (n>2)printf("%d\n",ans);
		else printf("%d\n",(n==1)?0:1);
	}
} 

