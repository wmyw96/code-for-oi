#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long LL;
const int MAX_N=10000001;
int c[MAX_N],P[MAX_N],g[MAX_N],s[MAX_N];
char mu[MAX_N];
int tot;

void init(){
	mu[1]=1;
	for (int i=2;i<MAX_N;i++){
		//if (i%100000==0) printf("%d\n",i);
		if (!c[i]){
			c[i]=i;
			P[++tot]=i;
		}
		int pt=(MAX_N-1)/i;
		for (int j=1;P[j]<=pt;j++){
			c[P[j]*i]=P[j];
			if (!(i%P[j])) break;
		}
		int now=i,mark=0,cnt=0;
		while (now>1){
			int ret=c[now];
			now/=ret;
			if (c[now]==ret){
				mark=1;
				mu[i]=0;
			}
			else g[i]+=mu[i/ret];
			cnt++;
		}
		if (!mark) mu[i]=(cnt%2)?(-1):(1);
		s[i]=s[i-1]+g[i];
		//printf("%d %d %d\n",i,mu[i],g[i]);
	}
}

int main(){
	int n,m,T;
	scanf("%d",&T);
	init();
	while (T--){
		scanf("%d%d",&n,&m);
		LL ans=0;
		for (int i=1;i<=min(n,m);){
			int nn=n/i;
			int nm=m/i;
			int nt=min(n/nn+1,m/nm+1);
			ans+=(LL)(s[nt-1]-s[i-1])*(m/i)*(n/i);
			i=nt;
		}
		cout<<ans<<endl;
	}
}

