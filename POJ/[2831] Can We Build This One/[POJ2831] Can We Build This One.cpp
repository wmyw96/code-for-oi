#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>
using namespace std;

const int MAX_M=200001,MAX_N=2001;
struct atype{
	int v,mx;
};
struct data{
	int x,y,w;
}E[MAX_M];
int nm,n,m;
int g[MAX_N*2],next[MAX_N*2],c[MAX_N],Ew[MAX_N*2];
int fa[MAX_N][21],mx[MAX_N][21],lg[MAX_N],d[MAX_N],Fa[MAX_N];
int x[MAX_M],y[MAX_M],w[MAX_M];

int cmp(data x,data y){
	return x.w<y.w;
}

void addedge(int x,int y,int w){
	g[++nm]=y;
	next[nm]=c[x];
	c[x]=nm;
	Ew[nm]=w;
}

void dfs(int i,int dep){
	d[i]=dep;
	for (int k=1;k<=lg[dep];k++){
		fa[i][k]=fa[fa[i][k-1]][k-1];
		mx[i][k]=max(mx[i][k-1],mx[fa[i][k-1]][k-1]);
	}
	for (int k=c[i];k;k=next[k]){
		int j=g[k];
		if (!~d[j]){
			fa[j][0]=i;
			mx[j][0]=Ew[k];
			dfs(j,dep+1);
		}
	}
}

atype up(int i,int k){
	atype ret;
	ret.mx=0;
	for (;k;k-=(1<<lg[k])){
		ret.mx=max(ret.mx,mx[i][lg[k]]);
		i=fa[i][lg[k]];
	}
	ret.v=i;
	return ret;
}

int lca(int a,int b){
	if (d[a]<d[b]) swap(a,b);
	if ((a=up(a,d[a]-d[b]).v)==b) return b;
	for (int k=lg[d[a]];k>=0;k--)
		if (fa[a][k]!=fa[b][k]){
			a=fa[a][k];
			b=fa[b][k];
		}
	return fa[a][0];
}

int find(int x){
	if (Fa[x]<0) return x;
	return Fa[x]=find(Fa[x]);
}

void init(){
	lg[1]=0;
	lg[2]=1;
	for (int i=3;i<MAX_N;i++)
	    lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i);
	memset(d,-1,sizeof d);
}

int main(){
	int T;
	init();
	scanf("%d%d%d",&n,&m,&T);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&x[i],&y[i],&w[i]);
		E[i].x=x[i];E[i].y=y[i];E[i].w=w[i];
	}
	sort(E+1,E+1+m,cmp);
	for (int i=1;i<=n;i++) Fa[i]=d[i]=-1;
	int edge=0;
	for (int i=1;i<=m && edge<n-1;i++){
	    int x=find(E[i].x);
	    int y=find(E[i].y);
	    if (x!=y){
	    	edge++;
	    	addedge(E[i].x,E[i].y,E[i].w);
	    	addedge(E[i].y,E[i].x,E[i].w);
	    	if (Fa[x]<Fa[y]) Fa[x]+=Fa[y],Fa[y]=x;
	    				else Fa[y]+=Fa[x],Fa[x]=y;
	    }
	}
	dfs(1,0);

	while (T--){
		int mark,dat;
		scanf("%d%d",&mark,&dat);
		int v=x[mark];
		int u=y[mark];
		if (u!=v){
			int t=lca(u,v);
			int ret=max(up(u,d[u]-d[t]).mx,up(v,d[v]-d[t]).mx);
			if (dat<=ret) printf("Yes\n"); else printf("No\n");
	    } else printf("No\n");
	}
}

