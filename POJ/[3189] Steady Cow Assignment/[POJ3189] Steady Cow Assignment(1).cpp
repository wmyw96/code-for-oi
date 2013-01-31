#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;

const int SUP=1000000000,MAX_N=2001,MAX_M=5000001;
int g[MAX_M],next[MAX_M],c[MAX_N],flow[MAX_M],cost[MAX_M];
int ed[MAX_N],E[MAX_N],pre[MAX_N],d[MAX_N];
int n,m,S,T,nm,ans;
int rank[MAX_N][51];
int wi[51];
int Q[MAX_M];

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
	int w=0;
	for (int k=c[i];k!=-1 && w<now;k=next[k]){
		int j=g[k],ret=min(flow[k],now-w);
		if (d[j]==d[i]+1 && flow[k])
		if ((ret=dfs(j,ret))){
			flow[k]-=ret;flow[k^1]+=ret;
			w+=ret;
		}
	}
	if (!w) d[i]=-1;
	return w;
}

int check(int l,int r){
	memset(c,-1,sizeof c);
	nm=0;
	for (int i=1;i<=n;i++){
		add(S,i,1);
		for (int j=l;j<=r;j++)
			add(i,rank[i][j]+n,1);
	}
	for (int i=1;i<=m;i++) add(i+n,T,wi[i]);
	int ans1=0;
	while (bfs()){
		int ret=0;
		while (1){
			ret=dfs(S,SUP);
			if (!ret) break; else ans1+=ret;
		}
	}
	return ans1>=n;
}

int main(){
	int x;
	scanf("%d%d",&n,&m);
	S=n+m+1;
	T=S+1;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			scanf("%d",&rank[i][j]);
	}
	for (int i=1;i<=m;i++) scanf("%d",&wi[i]);
	int ans=0;
	for (int len=1;len<=m && !ans;len++){
		for (int i=1;i<=m && !ans;i++)
			if (check(i,i+len-1)) {ans=len;break;}
	}
	printf("%d\n",ans);
} 
