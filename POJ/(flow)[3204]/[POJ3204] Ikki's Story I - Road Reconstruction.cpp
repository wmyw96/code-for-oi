#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
using namespace std;

const int MAX_N=5001,MAX_M=500001,SUP=1000000000;
int next[MAX_M],g[MAX_M],flow[MAX_M],Q[MAX_M],c[MAX_N];
int d[MAX_N];
int x[MAX_M],y[MAX_M],w[MAX_M],mark[MAX_N],mm[MAX_M];
int n,m,S,T,nm;

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
			flow[k]-=ret;mm[k/2+1]=1;flow[k^1]+=ret;
			w+=ret;
		}
	}
	if (!w) d[i]=-1;
	return w;
}
void dfs1(int i){
	mark[i]=1;
	for (int k=c[i];k!=-1;k=next[k]){
		int j=g[k];
		if (mark[j]==0 && flow[k]) dfs1(j); 
	}
}

void dfs2(int i){
	mark[i]=-1;
	for (int k=c[i];k!=-1;k=next[k]){
		int j=g[k];
		if (mark[j]==0 && flow[k^1]) dfs2(j); 
	}
}

int main(){
	scanf("%d%d",&n,&m);
	S=1;T=n;
	memset(c,-1,sizeof c);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&x[i],&y[i],&w[i]);
		x[i]++;y[i]++;
		add(x[i],y[i],w[i]);
	}
	while (bfs()){
		while (1){
			int ret=dfs(S,SUP);
			if (!ret) break;
		}
	}
	//printf("--\n");
	dfs1(S);
	dfs2(T);
	int ans=0;
	for (int i=1;i<=m;i++) ans+=(mark[x[i]]*mark[y[i]]==-1)*(mm[i]);
	printf("%d\n",ans);
}
/*
4 6
0 1 4
0 2 2
1 2 2
1 3 1
2 3 7
2 0 1
*/

