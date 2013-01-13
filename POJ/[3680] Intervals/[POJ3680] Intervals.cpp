#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
const int MAX=1000000,INF=-100000000,MAX_N=1001,MAX_M=100001;
set<int> ST;
map<int,int> M;
set<int>::iterator tmp;


int ud[MAX_N],Q[MAX_M*10],pre[MAX_N],E[MAX_N],d[MAX_N];
int g[MAX_M],next[MAX_M],cost[MAX_M],flow[MAX_M],c[MAX_N];
int ansc,S,T,n,N,nm,k;
int a[MAX_N],b[MAX_N],w[MAX_N];

int spfa(){
	memset(ud,0,sizeof ud);
	for (int i=1;i<=T;i++) d[i]=((S==i)?(0):(INF));
	Q[1]=S;
	for (int l=1,r=1;l<=r;l++){
		int i=Q[l];
		ud[i]=0;
		for (int k=c[i];k!=-1;k=next[k]){
			int j=g[k];
			if (flow[k]>0 && d[i]+cost[k]>d[j]){
				d[j]=d[i]+cost[k];
				E[j]=k;
				pre[j]=i;
				if (!ud[j]) Q[++r]=j,ud[j]=1;
			} 
		}
	}
	return d[T]!=INF;
}

void aug(){
	int ret=-INF;
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
	int Ti;
	scanf("%d",&Ti);
	while (Ti--){
		scanf("%d%d",&n,&k);
		ST.clear();
		
		for (int i=1;i<=n;i++){
			scanf("%d%d%d",&a[i],&b[i],&w[i]);
			ST.insert(a[i]);
			ST.insert(b[i]);
		}
		memset(c,-1,sizeof c);
		nm=0;
		N=0;
		
		for (tmp=ST.begin();tmp!=ST.end();tmp++){
			M[*tmp]=++N;
		}		
		int SS,TT;
		S=N+1;T=S+1;
		add(S,1,k,0);
		add(N,T,k,0);
		
		for (int i=1;i<N;i++) add(i,i+1,k,0);
		for (int i=1;i<=n;i++){
			if (a[i]>b[i]) swap(a[i],b[i]);
			add(M[a[i]],M[b[i]],1,w[i]);
		}
		ansc=0;
		while (spfa()) aug();
		printf("%d\n",ansc);
	}
}



