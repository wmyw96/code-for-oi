#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N=100001;
int n,m,cnt;
int P[MAX_N],c[MAX_N],u[MAX_N];
LL ans;

void init(){
	u[1]=1;
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
	}
}
int main(){
	scanf("%d%d",&n,&m);
	init();
	for (int T=1;T<=min(n,m);T++){
		LL ans1=0;
		for (int i=1;(LL)i*i<T;i++)
			if (T%i==0)
				ans1+=i*u[T/i]+(T/i)*u[i];
		int p=(int)sqrt(T);
		if (p*p==T) ans1+=p*u[p];
		ans+=ans1*(n/T)*(m/T);
	}
	cout<<2*ans-(LL)n*m<<endl;
} 


