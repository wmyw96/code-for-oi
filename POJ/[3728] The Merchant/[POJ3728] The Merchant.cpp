#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

struct data{
	int adown,aup,mx,mn,v;
};

const int INF=2147483647,MAX_N=66666;
int mx[MAX_N][21],mn[MAX_N][21],ans[MAX_N][21][2],fa[MAX_N][21],d[MAX_N];
int c[MAX_N*2],next[MAX_N*2],g[MAX_N*2],lg[MAX_N],val[MAX_N];
int n,nm;

// 0 down
// 1 up

int update(int i,int k,int D){
	int ret=0;
	ret=max(ans[i][k-1][D],ans[fa[i][k-1]][k-1][D]);
    ret=max(ret,(D) ? mx[fa[i][k-1]][k-1] - mn[i][k-1] : mx[i][k-1] - mn[fa[i][k-1]][k-1]);
    return ret;
}

void dfs(int i,int dep){
	d[i]=dep;
	mn[i][0]=min(val[i],(fa[i][0]) ? val[fa[i][0]]:INF);
	mx[i][0]=max(val[i],val[fa[i][0]]);
	ans[i][0][0]=fa[i][0] ? max(0,val[i]-val[fa[i][0]]) : 0;
	ans[i][0][1]=fa[i][0] ? max(0,val[fa[i][0]]-val[i]) : 0;
	for (int k=1;k<=lg[dep];k++){
		fa[i][k]=fa[fa[i][k-1]][k-1];
		mn[i][k]=min(mn[i][k-1], mn[fa[i][k-1]][k-1]);
		mx[i][k]=max(mx[i][k-1], mx[fa[i][k-1]][k-1]);
		ans[i][k][0]=update(i,k,0);
		ans[i][k][1]=update(i,k,1);
	}
	for (int k=c[i];k;k=next[k]){
		int j=g[k];
		if (!~d[j]){
			fa[j][0]=i;
			dfs(j,dep+1);
		}
	}
}

void addedge(int x,int y){
	g[++nm]=y;
	next[nm]=c[x];
	c[x]=nm;
}

void init(){
	lg[1]=0;
	lg[2]=1;
	for (int i=3;i<MAX_N;i++)
	    lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i);
	memset(d,-1,sizeof d);
}

data up(int i,int k){
	 data ret;
	 ret.aup=ret.adown=0;
	 ret.mx=ret.mn=val[i];
	 for (;k;k-=(1<<lg[k])){
		 ret.aup=max(ret.aup,ans[i][lg[k]][1]);
		 ret.aup=max(ret.aup,mx[i][lg[k]]-ret.mn);
		 ret.adown=max(ret.adown,ans[i][lg[k]][0]);
		 ret.adown=max(ret.adown,ret.mx-mn[i][lg[k]]);
		 ret.mx=max(ret.mx,mx[i][lg[k]]);
		 ret.mn=min(ret.mn,mn[i][lg[k]]);
		 i=fa[i][lg[k]];
	 }
	 ret.v=i;
	 return ret;
}

int lca(int a,int b){
	if (d[a]<d[b]) swap(a,b);
	if ((a=up(a,d[a]-d[b]).v)==b) return b;
	for (int k=lg[d[a]];k>=0;--k){
		if (fa[a][k]!=fa[b][k])
		   a=fa[a][k],
		   b=fa[b][k];
	}
	return fa[a][0];
}

int calc(int a,int b){
	int t=lca(a,b);
	if (t==a) return up(b,d[b]-d[t]).adown;
	if (t==b) return up(a,d[a]-d[t]).aup;
	data ra=up(a,d[a]-d[t]);
	data rb=up(b,d[b]-d[t]);
	return max(rb.mx-ra.mn,max(ra.aup,rb.adown));
}

int main(){
	init();
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for (int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		addedge(x,y);
		addedge(y,x);
	}
	dfs(1,0);
	int m;
	scanf("%d",&m);
	while (m--){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",calc(x,y));
	}
} 

