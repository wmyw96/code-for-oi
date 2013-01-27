#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N=1001,MAX_M=1000001,SUP=1000000000;
int next[MAX_M],g[MAX_M],flow[MAX_M],Q[MAX_M],c[MAX_N];
int d[MAX_N];
int N,F,D,S,T,nm;

void addedge(int x,int y,int w){
	g[nm]=y;
	next[nm]=c[x];
	c[x]=nm;
	flow[nm]=w;
	nm++;
}

void add(int x,int y,int w){
	addedge(x,y,w);
	addedge(y,x,0);
}

int bfs(){
	Q[1]=S;
	memset(d,-1,sizeof d);
	d[S]=0;
	for (int l=1,r=1;l<=r;l++){
		int i=Q[l];
		for (int k=c[i];k!=-1;k=next[k]){
			int j=g[k];
			if (d[j]==-1 && flow[k]) d[j]=d[i]+1,Q[++r]=j;
		}
	}
	return d[T]!=-1;
}

int dfs(int i,int now){
	if (now==0) return 0;
	if (i==T) return now;
	for (int k=c[i];k!=-1;k=next[k]){
		int j=g[k],ret=min(flow[k],now);
		if (d[j]==d[i]+1 && flow[k] && (ret=dfs(j,ret))){
			flow[k]-=ret;flow[k^1]+=ret;
			return ret;
		}
	}
	return 0;
}

int main(){
	int fi,di,k;
	scanf("%d%d%d",&N,&F,&D);
	memset(c,-1,sizeof c);
	S=F+D+2*N+1;
	T=S+1;
	for (int i=1;i<=F;i++) add(S,i,1);
	for (int i=1;i<=D;i++) add(i+F,T,1);
	for (int i=1;i<=N;i++){
		add(i+D+F,i+D+F+N,1);
		scanf("%d%d",&fi,&di);
		for (int j=1;j<=fi;j++){
			scanf("%d",&k);
			add(k,i+D+F,1);
		}
		for (int j=1;j<=di;j++){
			scanf("%d",&k);
			add(i+D+F+N,k+F,1);
		}
	}
	int ans=0;
	while (bfs()){
		int ret=0;
		while (1){
			ret=dfs(S,SUP);
			if (!ret) break;
			ans+=ret;
		}
	}
	printf("%d\n",ans);
}

