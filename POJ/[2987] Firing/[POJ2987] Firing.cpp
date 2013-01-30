#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;

typedef long long LL;
const int MAX_N=50001,MAX_M=5000001,SUP=1000000000;
int next[MAX_M],g[MAX_M],flow[MAX_M],Q[MAX_M],c[MAX_N];
int d[MAX_N];
int N,M,S,T,nm,ansn;

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

void dfs2(int i){ 
	d[i]=1;
	ansn++;
	for (int k=c[i];k!=-1;k=next[k]){
		int j=g[k];
		if (flow[k] && d[j]==-1) dfs2(j); 
	}
}

int main(){
	int l,r,x,y;
	while (scanf("%d%d",&N,&M)!=EOF){
	nm=0;
	ansn=0;
	S=N+1;T=S+1;
	memset(c,-1,sizeof c);
	LL ans1=0;
	
	for (int i=1;i<=N;i++){
		scanf("%d",&x);
		if (x>=0) ans1+=x,add(S,i,x);
		else add(i,T,-x);
	}
	for (int i=1;i<=M;i++){
		scanf("%d%d",&x,&y);
		add(x,y,SUP);
	}
	
	LL ans=0;
	while (bfs()){
		int ret=0;
		while (1){
			ret=dfs(S,SUP);
			if (!ret) break;
			ans+=ret;
		}
	}
	memset(d,-1,sizeof d); 
	dfs2(S);
	printf("%d ",ansn-1);
	cout<<ans1-ans<<endl;
	}
}

