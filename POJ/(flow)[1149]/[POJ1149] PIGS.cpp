#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<set>
using namespace std;
set<int> SS[2001];
set<int>::iterator iter;

const int MAX_N=222,MAX_M=1000001;
const int SUP=1000000000;
int g[MAX_M],next[MAX_M],c[MAX_N],flow[MAX_M],nm;
int Q[MAX_M],d[MAX_N];
int a[MAX_N*20],p[MAX_N*20];
int n,m,ans,S,T;


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
	if (i==T) return now;
	if (now==0) return 0;
	for (int k=c[i];k!=-1;k=next[k]){
		int j=g[k],ret1=min(now,flow[k]),ret=0;
		if (d[j]==d[i]+1 && flow[k] && (ret=dfs(j,ret1))){
			flow[k]-=ret;
			flow[k^1]+=ret;
			return ret;
		}
	}
	return 0;
}

int main(){
	scanf("%d%d",&m,&n);
	memset(c,-1,sizeof c);
	S=n+1;T=n+2;
	int A,B,K;
	for (int i=1;i<=m;i++){
		scanf("%d",&a[i]);
	}
	for (int i=1;i<=n;i++){
		scanf("%d",&A);
		for (int j=1;j<=A;j++){
			scanf("%d",&K);
			SS[K].insert(i);
		}
		scanf("%d",&B);
		add(i,T,B); 
	}
	for (int i=1;i<=m;i++){
		iter=SS[i].begin();
		if (iter!=SS[i].end()){
			add(S,*iter,a[i]);
			int rt=0;
			for (;iter!=SS[i].end();iter++) p[++rt]=*iter;
			for (int j=1;j<rt;j++)
				for (int k=j+1;k<=rt;k++)
					add(p[j],p[k],SUP);
		}
	}
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
