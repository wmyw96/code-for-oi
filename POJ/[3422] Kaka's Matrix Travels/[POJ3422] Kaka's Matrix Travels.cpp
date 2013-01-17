#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int INF=100000000,MAX_N=11111,MAX_M=500001;
int ud[MAX_N],Q[MAX_M*10],pre[MAX_N],E[MAX_N],d[MAX_N];
int g[MAX_M],next[MAX_M],cost[MAX_M],flow[MAX_M],c[MAX_N];
int ansc,S,T,n,N,nm,k;
int a[201][201],cnt; 

int spfa(){
	memset(ud,0,sizeof ud);
	for (int i=1;i<=T;i++) d[i]=((S==i)?(0):(-INF));
	Q[1]=S;
	for (int l=1,r=1;l<=r;l++){
		int i=Q[l];
		ud[i]=0;
		for (int k=c[i];k!=-1;k=next[k]){
			int j=g[k];
			//printf("-- %d %d %d\n",d[i],cost[k],d[j]);
			if (flow[k]>0 && d[i]+cost[k]>d[j]){
				
				d[j]=d[i]+cost[k];
				E[j]=k;
				pre[j]=i;
				if (!ud[j]) Q[++r]=j,ud[j]=1;
			} 
		}
	}
	return d[T]!=-INF;
}

void aug(){
	int ret=INF;
	for (int i=T;i!=S;i=pre[i])
		ret=min(ret,flow[E[i]]);
	for (int i=T;i!=S;i=pre[i]){
		flow[E[i]]-=ret;
		flow[E[i]^1]+=ret;
		ansc+=ret*cost[E[i]];
	}
}

void addedge(int x,int y,int f,int ct){
	g[nm]=y;
	next[nm]=c[x];
	c[x]=nm;
	cost[nm]=ct;
	flow[nm]=f;
	nm++;
}

void add(int x,int y,int f,int ct){
	addedge(x,y,f,ct);
	addedge(y,x,0,-ct);
}

int main(){
	scanf("%d%d",&n,&k);
	memset(c,-1,sizeof c);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			int x;
			scanf("%d",&x);
			a[i][j]=++cnt;
			add(cnt,cnt+n*n,1,x);
			add(cnt,cnt+n*n,INF,0);
		}
	}
	N=n*n;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			if (i+1<=n) add(a[i][j]+N,a[i+1][j],INF,0);
			if (j+1<=n) add(a[i][j]+N,a[i][j+1],INF,0);
		} 
	S=N*2+1;T=N*2+2;
	add(S,1,k,0);
	add(N+N,T,k,0);
	while (spfa()) aug();
	printf("%d\n",ansc);
}
