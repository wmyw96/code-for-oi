#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long LL;
const int MAX_N=1100001;
int c[MAX_N],P[MAX_N],g[MAX_N],s[MAX_N];
char mu[MAX_N];
int tot;

void init(){
	mu[1]=1;
	for (int i=2;i<MAX_N;i++){
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
	}
}

LL sqr3(int i){
	return (LL)i*i*i;
}

LL sqr(int i){
	return (LL)i*i;
}

int main(){
	int n,m,T;
	scanf("%d",&T);
	init();
	while (T--){
		scanf("%d",&n);
		LL ans=0,ans1=0;
		for (int i=1;i<=n;i++){
			ans+=mu[i]*sqr3(n/i);
			//printf("--- %d %d\n",mu[i],sqr3(n/i));
		}
		for (int i=1;i<=n;i++){
			ans1+=mu[i]*sqr(n/i);
			//printf("+++ %d %d\n",mu[i],sqr(n/i));
		}
		cout<<ans+ans1*3+3<<endl;
	}
}

