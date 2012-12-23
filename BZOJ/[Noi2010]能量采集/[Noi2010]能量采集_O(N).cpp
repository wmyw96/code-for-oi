#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N=10000001;
int n,m,cnt;
int P[MAX_N],c[MAX_N],u[MAX_N],su[MAX_N];
LL ans;

void init(){
	u[1]=1;
	su[1]=1; 
	for (int i=2;i<MAX_N;i++){
		if (!c[i]){
			c[i]=i;
			u[i]=-1;
			P[++cnt]=i;
		}
		for (int j=1;j<=cnt;j++){
			if ((LL)i*P[j]>=MAX_N) break;
			c[i*P[j]]=P[j];
			if (c[i]==P[j]) u[i*P[j]]=0;
						else u[i*P[j]]=-u[i];
			if (i%P[j]==0) break;
		}
		su[i]=su[i-1]+u[i];
	}
}

LL calc_g(int L,int R){
	LL ret=0;
	for (int i=1;i<=R;i++)
		ret+=i*(su[R/i]-su[(L-1)/i]);
	return ret;
}

int main(){
	scanf("%d%d",&n,&m);
	init();
	for (int T=1;T<=min(n,m);){
		int nn=(n/T);
		int mm=(m/T);
		int nt=min(n/nn+1,m/mm+1);
		ans+=calc_g(T,nt-1)*(n/T)*(m/T);
		T=nt;
	}
	cout<<2*ans-(LL)n*m<<endl;
} 


