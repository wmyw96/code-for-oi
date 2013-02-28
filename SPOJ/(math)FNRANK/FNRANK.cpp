#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAX_N=100001;
int tot,ans,T,n,a,b,NN,tt,N;
int c[MAX_N],P[MAX_N];
int p[11];
typedef long long LL;
LL rnk;

void dfs(int dep,int now,int cc){
	if (dep==tt){
		NN+=(N/now)*((cc%2==0)?(1):(-1));
		return;
	}
	dfs(dep+1,now,cc);
	if ((LL)now*p[dep+1]<=N) dfs(dep+1,now*p[dep+1],cc+1);
}

int main(){
	c[1]=0;
	for (int i=2;i<MAX_N;i++){
		if (!c[i]) P[++tot]=i,c[i]=i;
		for (int j=1;j<=tot;j++){
			if ((LL)i*P[j]<MAX_N)
				c[i*P[j]]=P[j];
			else break;
			if (i%P[j]==0) break;
		}
	}
	
	scanf("%d",&T);
	while (T--){
		scanf("%d%d%d",&n,&a,&b);
		rnk=0;
		
		for (int i=1;i<=n;i++){
			N=(LL)i*a/b;
			int num=i;	int check=0;
			tt=0;
			while (num!=1){
				int x=c[num];
				num/=x;
				if (x!=c[num]) p[++tt]=x;
			}
			NN=0;
			dfs(0,1,0);
			rnk+=NN;
		}
		
		rnk++;
		printf("%lld\n",rnk);
	}
}


