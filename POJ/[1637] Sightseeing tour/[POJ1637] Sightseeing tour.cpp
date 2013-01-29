#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;

const int MAX_N=50001,MAX_M=5000001,SUP=1000000000;
int next[MAX_M],g[MAX_M],flow[MAX_M],Q[MAX_M],c[MAX_N];
int d[MAX_N];
int n,m,S,T,nm;
int in[MAX_N],out[MAX_N],x[MAX_M],y[MAX_M],mark[MAX_N];

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

void solve(){
	scanf("%d%d",&n,&m);
	memset(in,0,sizeof in);
	memset(out,0,sizeof out);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&x[i],&y[i],&mark[i]);
		in[y[i]]++;out[x[i]]++;
	}
	nm=0;
	S=n+1;T=n+2;
	memset(c,-1,sizeof c);
	int check=1;
	int ans1=0;
	for (int i=1;i<=n;i++){
		if (abs(in[i]-out[i])%2!=0){
			check=0;break;
		}
		if (in[i]-out[i]<0) add(S,i,(out[i]-in[i])/2),ans1+=(out[i]-in[i])/2;
		if (in[i]-out[i]>0) add(i,T,(in[i]-out[i])/2);
	}
	if (check){
		for (int i=1;i<=m;i++){
		 	if (!mark[i]) add(x[i],y[i],1);
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
		printf("%s\n",(ans-ans1==0)?("possible"):("impossible"));
	}
	else printf("impossible\n");
}

int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}

