#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;
typedef long long LL;
const LL SUP=100000000000000LL;
const int MAX_N=601,MAX_M=500001;
int n,m,all,nm,S,T;
int g[MAX_M],next[MAX_M],c[MAX_N],flow[MAX_M],Q[MAX_N*2];
int d[MAX_N],a[MAX_N],b[MAX_N];
LL gm[MAX_N][MAX_N];
LL p[MAX_N*MAX_N];
set<LL> SS;
set<LL>::iterator tmp;

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
			if (flow[k] && d[j]==-1) d[j]=d[i]+1,Q[++r]=j;
		}
	} 
	return d[T]!=-1;
}

int dfs(int i,int now){
	if (!now) return 0;
	if (i==T) return now;
	for (int k=c[i];k!=-1;k=next[k]){
		int j=g[k],ret=min(flow[k],now);
		if (d[j]==d[i]+1 && (ret=dfs(j,ret))){
			flow[k]-=ret;
			flow[k^1]+=ret;
			return ret;
		}
	}
	return 0;
}

int check(LL sup){
	memset(c,-1,sizeof c);
	nm=0;
	S=n*2+1;T=S+1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (gm[i][j]<=sup) add(i,j+n,1000000000);
	for (int i=1;i<=n;i++) add(S,i,a[i]);
	for (int i=1;i<=n;i++) add(i+n,T,b[i]);
	int ans=0;
	while (bfs()){
		int ret=0;
		while (1){
			ret=dfs(S,1000000000);
			if (!ret) break;
			ans+=ret;
		}
	}
	return (ans==all);
}

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]),all+=a[i];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (i!=j) gm[i][j]=SUP;
	for (int i=1;i<=m;i++){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		if (w<gm[x][y]) gm[x][y]=gm[y][x]=w;
	}
	LL UP=SUP;
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
		if (i!=k)
			for (int j=1;j<=n;j++)
			if (j!=k && j!=i){
				gm[i][j]=min(gm[i][j],gm[i][k]+gm[k][j]);
			}
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++) 
			if (gm[i][j]!=SUP) SS.insert(gm[i][j]);
	int len=0;
	for (tmp=SS.begin();tmp!=SS.end();tmp++) p[++len]=*tmp;
	LL l=0,r=len+1;
	while (l+1<r){
		LL mid=(l+r)/2;
		if (check(p[mid])) r=mid;else l=mid;
	}
	if (r!=len+1) cout<<p[r]<<endl; else cout<<-1<<endl;
}

